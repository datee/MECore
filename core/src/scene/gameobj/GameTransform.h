//
// Created by ryen on 12/14/24.
//

#ifndef GAMETRANSFORM_H
#define GAMETRANSFORM_H
#include "GameObjectModule.h"
#include "math/Transform.h"

namespace me::scene {
    class GameTransform final : public GameObjectModule {
        private:
        math::Transform world;
        math::Transform local;
        math::Vector3 eulerAngles;

        public:
        explicit GameTransform(GameObject* obj);

        [[nodiscard]] inline math::Vector3 GetPosition() const { return world.position; }
        [[nodiscard]] inline math::Quaternion GetRotation() const { return world.rotation; }
        [[nodiscard]] inline math::Vector3 GetAngles() const { return eulerAngles; }
        [[nodiscard]] inline math::Vector3 GetScale() const { return world.scale; }

        [[nodiscard]] inline math::Transform& GlobalRaw() { return world; }
        [[nodiscard]] inline math::Transform& LocalRaw() { return local; }

        void SetGlobalPosition(const math::Vector3& pos);
        void SetGlobalRotation(const math::Quaternion& rot);

        void SetLocalPosition(const math::Vector3& pos);
        void SetLocalRotation(const math::Quaternion& rot);
        void SetLocalScale(const math::Vector3& scale);
    };
}


#endif //GAMETRANSFORM_H
