//
// Created by ryen on 12/31/24.
//

#include "PhysicsWorld.h"

#include "physics/PhysicsGlobals.h"
#include "time/TimeGlobal.h"

namespace me::scene {
    PhysicsWorld::PhysicsWorld(int stepsPerSecond) {
        timeStep = 1.0F / stepsPerSecond;
        accumulator = 0;
        physicsSystem.Init(65536, 0, 65536, 10240, bpLayerInterface, objVBpFilter, objPairFilter);
    }

    inline bool PhysicsWorld::CanUpdate() const {
        return accumulator >= timeStep;
    }

    bool PhysicsWorld::TryUpdate() {
        accumulator += time::mainGame.GetElapsed();

        if (CanUpdate()) {
            Update(timeStep);
            accumulator -= timeStep;
            return true;
        }
        return false;
    }

    void PhysicsWorld::Update(const float timeStep) {
        physicsSystem.Update(timeStep, 1, physics::tempAllocator, physics::jobSystemPool);
    }

    void PhysicsWorld::Optimize() {
        physicsSystem.OptimizeBroadPhase();
    }

}
