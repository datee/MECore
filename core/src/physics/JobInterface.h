//
// Created by ryen on 12/31/24.
//

#ifndef JOBINTERFACE_H
#define JOBINTERFACE_H

#include <Jolt/Jolt.h>
#include <Jolt/Core/JobSystemWithBarrier.h>

// WICKED ENGINE DOESNT EVEN ATTACH THE WI JOB SYSTEM TO JOLT? ?? ???
// i feel so dumb i have to do it myself now.. ........

namespace me::physics {
    class JobInterface : public JPH::JobSystemWithBarrier {
        virtual int GetMaxConcurrency() const override;
        virtual JobHandle CreateJob(const char* inName, JPH::ColorArg inColor, const JobFunction& inJobFunction, JPH::uint32 inNumDependencies) override;
        virtual void FreeJob(Job* inJob) override;
        virtual void QueueJob(Job* inJob) override;
        virtual void QueueJobs(Job** inJobs, JPH::uint inNumJobs) override;
    };
}

#endif //JOBINTERFACE_H
