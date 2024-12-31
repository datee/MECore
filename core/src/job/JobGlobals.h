//
// Created by ryen on 12/30/24.
//

#ifndef JOBGLOBALS_H
#define JOBGLOBALS_H

#include "JobSystem.h"

namespace me::job {
    inline std::unique_ptr<JobSystem> mainSystem;

    bool Initialize(uint32_t maxThreads = ~0u);
    void Shutdown();
}

#endif //JOBGLOBALS_H
