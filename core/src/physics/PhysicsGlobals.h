//
// Created by ryen on 12/31/24.
//

#ifndef PHYSICSGLOBALS_H
#define PHYSICSGLOBALS_H

#include <Jolt/Jolt.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>

namespace me::physics {
    inline JPH::TempAllocator* tempAllocator = nullptr;
    inline JPH::JobSystemThreadPool* jobSystemPool = nullptr;

    bool Initialize();
    void Shutdown();
}

#endif //PHYSICSGLOBALS_H
