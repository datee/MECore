//
// Created by ryen on 12/30/24.
//

#include "JobSystem.h"

#include <cassert>
#include <mutex>

#include "MEPlatform.h"

#ifdef PLATFORM_LINUX
    #include <pthread.h>
    #include <sys/resource.h>
#elif defined(PLATFORM_WINDOWS)
    #include <Windows.h>
    #include <intrin.h>
#endif

namespace me::job {
    template <typename T>
    constexpr T clamp(T x, T a, T b) {
        return x < a ? a : (x > b ? b : x);
    }

    inline long AtomicAdd(volatile long* ptr, long value) {
        #ifdef PLATFORM_WINDOWS
        return _InterlockedExchangeAdd(ptr, value);
        #else
        return __atomic_fetch_add(ptr, value, __ATOMIC_SEQ_CST);
        #endif
    }

    inline long AtomicOr(volatile long* ptr, long mask) {
        #ifdef PLATFORM_WINDOWS
        return _InterlockedOr(ptr, mask);
        #else
        return __atomic_fetch_or(ptr, mask, __ATOMIC_SEQ_CST);
        #endif
    }

    inline long AtomicLoad(const volatile long* ptr) {
        return AtomicOr(const_cast<volatile long*>(ptr), 0);
    }

    inline void JobSystem::Job::Execute() {
        JobArgs args;
        args.groupID = groupID;
        if (sharedmemory_size > 0) {
            args.sharedMemory = alloca(sharedmemory_size);
        } else {
            args.sharedMemory = nullptr;
        }
        for (uint32_t i = groupJobOffset; i < groupJobEnd; ++i) {
            args.jobIndex = i;
            args.groupIndex = i - groupJobOffset;
            args.isFirstJobInGroup = (i == groupJobOffset);
            args.isLastJobInGroup = (i == groupJobEnd - 1);
            task(args);
        }

        AtomicAdd(&ctx->counter, -1);
    }

    inline void JobSystem::JobQueue::Push(const Job& job) {
        std::scoped_lock lock(locker);
        queue.push_back(job);
    }

    inline bool JobSystem::JobQueue::Pop(Job& job) {
        std::scoped_lock lock(locker);
        if (queue.empty()) {
            return false;
        }
        job = std::move(queue.front());
        queue.pop_front();
        return true;
    }

    inline void JobSystem::PriorityResources::Work(uint32_t startingQueue) {
        Job job;
        for (uint32_t i = 0; i < numThreads; ++i) {
            JobQueue& queue = jobQueuePerThread[startingQueue % numThreads];
            while (queue.Pop(job)) {
                job.Execute();
            }
            startingQueue++;
        }
    }

    JobSystem::InternalState::~InternalState() {
        Shutdown();
    }

    void JobSystem::InternalState::Shutdown() {
        alive.store(false);
        bool wakeLoop = true;
        std::thread waker([&] {
            while (wakeLoop) {
                for (auto& x : resources) {
                    x.wakeCondition.notify_all();
                }
            }
        });
        for (auto& x : resources) {
            for (auto& thread : x.threads) {
                thread.join();
            }
        }
        wakeLoop = false;
        waker.join();
        for (auto& x : resources) {
            x.jobQueuePerThread.reset();
            x.threads.clear();
            x.numThreads = 0;
        }
        numCores = 0;
    }

    JobSystem* JobSystem::Create(uint32_t maxThreadCount) {
        JobSystem* jobSystem = new JobSystem();

        maxThreadCount = std::max(1u, maxThreadCount);
        jobSystem->state.numCores = std::thread::hardware_concurrency();

        for (int i = 0; i < static_cast<int>(Priority::Count); ++i) {
            const Priority priority = static_cast<Priority>(i);
            PriorityResources& res = jobSystem->state.resources[i];

            switch (priority) {
                case Priority::High:
                    res.numThreads = jobSystem->state.numCores - 1;
                break;
                case Priority::Low:
                    res.numThreads = jobSystem->state.numCores - 2;
                break;
                case Priority::Streaming:
                    res.numThreads = 1;
                break;
                default:
                    assert(0);
                break;
            }
            res.numThreads = clamp(res.numThreads, 1u, maxThreadCount);
            res.jobQueuePerThread.reset(new JobQueue[res.numThreads]);
            res.threads.reserve(res.numThreads);

            for (uint32_t threadID = 0; threadID < res.numThreads; ++threadID) {
                #ifdef PLATFORM_LINUX
                std::thread& worker = res.threads.emplace_back([threadID, priority, &res, jobSystem] {
                    switch (priority) {
                    case Priority::Low:
                    case Priority::Streaming:
                        // from the sched(2) manpage:
                        // In the current [Linux 2.6.23+] implementation, each unit of
                        // difference in the nice values of two processes results in a
                        // factor of 1.25 in the degree to which the scheduler favors
                        // the higher priority process.
                        //
                        // so 3 would mean that other (prio 0) threads are around twice as important
                        if (setpriority(PRIO_PROCESS, 0, 3) != 0) {
                            perror("setpriority");
                        }
                        break;
                    case Priority::High:
                        // nothing to do
                            break;
                        default:
                            assert(0);
                        }
                #else
                std::thread& worker = res.threads.emplace_back([threadID, &res]) {
                #endif
                    while (jobSystem->state.alive.load()) {
                        res.Work(threadID);

                        std::unique_lock<std::mutex> lock(res.wakeMutex);
                        res.wakeCondition.wait(lock);
                    }
                });

                auto handle = worker.native_handle();

                int core = threadID + 1;
                if (priority == Priority::Streaming) {
                    core = jobSystem->state.numCores - 1 - threadID;
                }

                #ifdef PLATFORM_WINDOWS
                // Do Windows-specific thread setup:

                // Put each thread on to dedicated core:
                DWORD_PTR affinityMask = 1ull << core;
                DWORD_PTR affinity_result = SetThreadAffinityMask(handle, affinityMask);
                assert(affinity_result > 0);

                if (priority == Priority::High) {
                    BOOL priority_result = SetThreadPriority(handle, THREAD_PRIORITY_NORMAL);
                    assert(priority_result != 0);

                    std::wstring wthreadname = L"me::job_" + std::to_wstring(threadID);
                    HRESULT hr = SetThreadDescription(handle, wthreadname.c_str());
                    assert(SUCCEEDED(hr));
                } else if (priority == Priority::Low) {
                    BOOL priority_result = SetThreadPriority(handle, THREAD_PRIORITY_LOWEST);
                    assert(priority_result != 0);

                    std::wstring wthreadname = L"me::job_lo_" + std::to_wstring(threadID);
                    HRESULT hr = SetThreadDescription(handle, wthreadname.c_str());
                    assert(SUCCEEDED(hr));
                } else if (priority == Priority::Streaming) {
                    BOOL priority_result = SetThreadPriority(handle, THREAD_PRIORITY_LOWEST);
                    assert(priority_result != 0);

                    std::wstring wthreadname = L"me::job_st_" + std::to_wstring(threadID);
                    HRESULT hr = SetThreadDescription(handle, wthreadname.c_str());
                    assert(SUCCEEDED(hr));
                }
                #elif defined(PLATFORM_LINUX)
                #define handle_error_en(en, msg) \
                do { errno = en; perror(msg); } while (0)

                int ret;
                cpu_set_t cpuset;
                CPU_ZERO(&cpuset);
                size_t cpusetsize = sizeof(cpuset);

                CPU_SET(core, &cpuset);
                ret = pthread_setaffinity_np(handle, cpusetsize, &cpuset);
                if (ret != 0)
                    handle_error_en(ret, std::string(" pthread_setaffinity_np[" + std::to_string(threadID) + ']').c_str());

                if (priority == Priority::High) {
                    std::string thread_name = "me::job_" + std::to_string(threadID);
                    ret = pthread_setname_np(handle, thread_name.c_str());
                    if (ret != 0)
                        handle_error_en(ret, std::string(" pthread_setname_np[" + std::to_string(threadID) + ']').c_str());
                } else if (priority == Priority::Low) {
                    std::string thread_name = "me::job_lo_" + std::to_string(threadID);
                    ret = pthread_setname_np(handle, thread_name.c_str());
                    if (ret != 0)
                        handle_error_en(ret, std::string(" pthread_setname_np[" + std::to_string(threadID) + ']').c_str());
                    // priority is set in the worker function
                } else if (priority == Priority::Streaming) {
                    std::string thread_name = "me::job_st_" + std::to_string(threadID);
                    ret = pthread_setname_np(handle, thread_name.c_str());
                    if (ret != 0)
                        handle_error_en(ret, std::string(" pthread_setname_np[" + std::to_string(threadID) + ']').c_str());
                    // priority is set in the worker function
                }

                #undef handle_error_en
                #endif
            }
        }
        // wicked engine logs init time here
        return jobSystem;
    }

    uint32_t JobSystem::GetThreadCount(Priority priority) {
        return state.resources[static_cast<int>(priority)].numThreads;
    }

    JobSystem::~JobSystem() {
        state.Shutdown();
    }

    void JobSystem::Execute(JobContext& ctx, const std::function<void(JobArgs)>& task) {
        PriorityResources& res = state.resources[static_cast<int>(ctx.priority)];

        AtomicAdd(&ctx.counter, 1);

        Job job;
        job.ctx = &ctx;
        job.task = task;
        job.groupID = 0;
        job.groupJobOffset = 0;
        job.groupJobEnd = 1;
        job.sharedmemory_size = 0;

        if (res.numThreads < 1) {
            // If job system is not yet initialized, job will be executed immediately here instead of thread:
            job.Execute();
            return;
        }

        res.jobQueuePerThread[res.nextQueue.fetch_add(1) % res.numThreads].Push(job);
        res.wakeCondition.notify_one();
    }

    void JobSystem::Dispatch(JobContext& ctx, uint32_t jobCount, uint32_t groupSize, const std::function<void(JobArgs)>& task, size_t sharedmemory_size) {
        if (jobCount == 0 || groupSize == 0) {
            return;
        }
        PriorityResources& res = state.resources[static_cast<int>(ctx.priority)];

        const uint32_t groupCount = DispatchGroupCount(jobCount, groupSize);

        // Context state is updated:
        AtomicAdd(&ctx.counter, groupCount);

        Job job;
        job.ctx = &ctx;
        job.task = task;
        job.sharedmemory_size = (uint32_t)sharedmemory_size;

        for (uint32_t groupID = 0; groupID < groupCount; ++groupID)
        {
            // For each group, generate one real job:
            job.groupID = groupID;
            job.groupJobOffset = groupID * groupSize;
            job.groupJobEnd = std::min(job.groupJobOffset + groupSize, jobCount);

            if (res.numThreads < 1) {
                // If job system is not yet initialized, job will be executed immediately here instead of thread:
                job.Execute();
            } else {
                res.jobQueuePerThread[res.nextQueue.fetch_add(1) % res.numThreads].Push(job);
            }
        }
        if (res.numThreads > 1) {
            res.wakeCondition.notify_all();
        }
    }

    uint32_t JobSystem::DispatchGroupCount(uint32_t jobCount, uint32_t groupSize) {
        // Calculate the amount of job groups to dispatch (overestimate, or "ceil"):
        return (jobCount + groupSize - 1) / groupSize;
    }

    bool JobSystem::IsBusy(const JobContext& ctx) {
        // Whenever the context label is greater than zero, it means that there is still work that needs to be done
        return AtomicLoad(&ctx.counter) > 0;
    }

    void JobSystem::Wait(const JobContext& ctx) {
        if (IsBusy(ctx)) {
            PriorityResources& res = state.resources[static_cast<int>(ctx.priority)];

            // Wake any threads that might be sleeping:
            res.wakeCondition.notify_all();

            // work() will pick up any jobs that are on stand by and execute them on this thread:
            res.Work(res.nextQueue.fetch_add(1) % res.numThreads);

            while (IsBusy(ctx)) {
                // If we are here, then there are still remaining jobs that work() couldn't pick up.
                //	In this case those jobs are not standing by on a queue but currently executing
                //	on other threads, so they cannot be picked up by this thread.
                //	Allow to swap out this thread by OS to not spin endlessly for nothing
                std::this_thread::yield();
            }
        }
    }
}
