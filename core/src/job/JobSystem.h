//
// Created by ryen on 12/30/24.
//

#ifndef JOBSYSTEM_H
#define JOBSYSTEM_H

#include <functional>
#include <atomic>
#include <condition_variable>
#include <deque>

// Most of the job system is taken from turanszkij's Wicked Engine.
// He has an excellent article explaining how it works here.
// https://wickedengine.net/2018/11/simple-job-system-using-standard-c/
// WickedEngine is licensed under the MIT license.

namespace me::job {
	enum class Priority {
		High,		// Default
		Low,		// Pool of low priority threads, useful for generic tasks that shouldn't interfere with high priority tasks
		Streaming,	// Single low priority thread, for streaming resources
		Count
	};

	struct JobArgs {
		uint32_t jobIndex;		// job index relative to dispatch (like SV_DispatchThreadID in HLSL)
		uint32_t groupID;		// group index relative to dispatch (like SV_GroupID in HLSL)
		uint32_t groupIndex;	// job index relative to group (like SV_GroupIndex in HLSL)
		bool isFirstJobInGroup;	// is the current job the first one in the group?
		bool isLastJobInGroup;	// is the current job the last one in the group?
		void* sharedMemory;		// stack memory shared within the current group (jobs within a group execute serially)
	};

	// Defines a state of execution, can be waited on
	struct JobContext {
		volatile long counter = 0;
		Priority priority = Priority::High;
	};

	class JobSystem {
		private:
		struct Job {
			std::function<void(JobArgs)> task;
			JobContext* ctx;
			uint32_t groupID;
			uint32_t groupJobOffset;
			uint32_t groupJobEnd;
			uint32_t sharedmemory_size;

			void Execute();
		};
		struct JobQueue {
			std::deque<Job> queue;
			std::mutex locker;

			void Push(const Job& job);
			bool Pop(Job& job);
		};
		struct PriorityResources {
			uint32_t numThreads = 0;
			std::vector<std::thread> threads; // This used to be a wi::vector, don't know why.
			std::unique_ptr<JobQueue[]> jobQueuePerThread;
			std::atomic<uint32_t> nextQueue{ 0 };
			std::condition_variable wakeCondition;
			std::mutex wakeMutex;

			void Work(uint32_t startingQueue);
		};
		struct InternalState {
			uint32_t numCores = 0;
			PriorityResources resources[static_cast<int>(Priority::Count)];
			std::atomic_bool alive{ true };

			~InternalState();
			void Shutdown();
		};

		InternalState state;

		JobSystem() = default;
		public:
		~JobSystem();

		static JobSystem* Create(uint32_t maxThreadCount);
		static uint32_t DispatchGroupCount(uint32_t jobCount, uint32_t groupSize);

		uint32_t GetThreadCount(Priority priority = Priority::High);

		// Add a task to execute asynchronously. Any idle thread will execute this.
		void Execute(JobContext& ctx, const std::function<void(JobArgs)>& task);

		// Divide a task onto multiple jobs and execute in parallel.
		//	jobCount	: how many jobs to generate for this task.
		//	groupSize	: how many jobs to execute per thread. Jobs inside a group execute serially. It might be worth to increase for small jobs
		//	task		: receives a JobArgs as parameter
		void Dispatch(JobContext& ctx, uint32_t jobCount, uint32_t groupSize, const std::function<void(JobArgs)>& task, size_t sharedMemorySize = 0);

		// Check if any threads are working currently or not
		bool IsBusy(const JobContext& ctx);

		// Wait until all threads become idle
		//	Current thread will become a worker thread, executing jobs
		void Wait(const JobContext& ctx);
	};
}


#endif //JOBSYSTEM_H
