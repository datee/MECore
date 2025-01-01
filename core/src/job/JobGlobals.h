//
// Created by ryen on 12/30/24.
//

#ifndef JOBGLOBALS_H
#define JOBGLOBALS_H

#include "JobSystem.h"

// TODO: Verify that this job system is good.
// I have doubts about Wicked's job system after reading the source code (I bet it's good but I have gripes with it)
// and I don't want two of them running at the same time
// Maybe take a form of something like Unity's job system, where it is more abstracted.

namespace me::job {
    inline std::unique_ptr<JobSystem> mainSystem;

    bool Initialize(uint32_t maxThreads = ~0u);
    void Shutdown();
}

#endif //JOBGLOBALS_H
