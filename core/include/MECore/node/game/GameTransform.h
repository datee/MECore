//
// Created by ryen on 2/24/25.
//

#pragma once

#include "GameNodeModule.h"
#include "MECore/math/Transform.h"

namespace ME::node {
    class GameTransform final : public GameNodeModule {
        protected:
        Transform world;
        Transform local;

        public:
        explicit GameTransform(GameNode* node) : GameNodeModule(node) {
            world = Transform::Identity();
            local = Transform::Identity();
        }

        inline Vector3 GetPosition() const { return world.position; }
        inline Quaternion GetRotation() const { return world.rotation; }
        inline Vector3 GetScale() const { return world.scale; }
        inline Vector3 GetLocalPosition() const { return local.position; }
        inline Quaternion GetLocalRotation() const { return local.rotation; }
        inline Vector3 GetLocalScale() const { return local.scale; }

        inline Transform& Raw() { return world; }
        inline Transform& LocalRaw() { return local; }

        void SetPosition(const Vector3& position);
        void SetRotation(const Quaternion& rotation);
        void SetLocalPosition(const Vector3& position);
        void SetLocalRotation(const Quaternion& rotation);
        void SetLocalScale(const Vector3& scale);
    };
}
