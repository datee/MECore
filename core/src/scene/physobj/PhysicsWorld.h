//
// Created by ryen on 12/31/24.
//

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>

#include "physics/Layers.h"
#include "physics/Filters.h"

namespace me::scene {
    class PhysicsWorld {
        private:
        physics::BPLayerInterface bpLayerInterface;
        physics::ObjectPairFilter objPairFilter;
        physics::ObjectVBPFilter objVBpFilter;
        JPH::PhysicsSystem physicsSystem;

        float timeStep;
        float accumulator;

        public:
        explicit PhysicsWorld(int stepsPerSecond);

        [[nodiscard]] inline JPH::BodyInterface& GetInterface() { return physicsSystem.GetBodyInterface(); }

        // Tries to update the physics if enough time has passed.
        bool TryUpdate();
        // Runs the physics simulation
        void Update(float timeStep);

        void Optimize();
    };
}

#endif //PHYSICSWORLD_H
