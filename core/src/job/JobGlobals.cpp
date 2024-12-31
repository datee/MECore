//
// Created by ryen on 12/30/24.
//

#include "JobGlobals.h"

#include "spdlog/spdlog.h"

namespace me::job {
    bool Initialize(uint32_t maxThreads) {
        JobSystem* system = JobSystem::Create(maxThreads);
        if (!system) {
            spdlog::critical("Failed to create job system");
            return false;
        }

        mainSystem = std::unique_ptr<JobSystem>(system);
        return true;
    }

    void Shutdown() {
        if (mainSystem) {
            mainSystem = nullptr;
        }
    }
}
