//
// Created by ryen on 12/14/24.
//

#ifndef GAMETRANSFORM_H
#define GAMETRANSFORM_H
#include "../../math/Transform.h"

namespace me::scene {
    class GameTransform {
        private:
        math::Transform global;
        math::Vector3 eulerAngles;

        public:
        GameTransform() {
            global = math::Transform::identity;
            eulerAngles = math::Vector3(0, 0, 0);
        }

        [[nodiscard]] inline math::Vector3 GetPosition() const { return global.position; }
        [[nodiscard]] inline math::Quaternion GetRotation() const { return global.rotation; }
        [[nodiscard]] inline math::Vector3 GetAngles() const { return eulerAngles; }
        [[nodiscard]] inline math::Vector3 GetScale() const { return global.scale; }
        [[nodiscard]] inline math::Vector3 GetRight() const { return global.Right(); }
        [[nodiscard]] inline math::Vector3 GetUp() const { return global.Up(); }
        [[nodiscard]] inline math::Vector3 GetForward() const { return global.Forward(); }
        [[nodiscard]] inline math::Transform& Raw() { return global; }

        inline void SetPosition(const math::Vector3 pos) { global.position = pos; }
        inline void SetRotation(const math::Quaternion rot) { global.rotation = rot; eulerAngles = rot.ToEulerAngles(); }
        inline void SetAngles(const math::Vector3 angles) { eulerAngles = angles; global.rotation = math::Quaternion::FromEulerAngles(angles * mathfu::kDegreesToRadians); }
        inline void SetScale(const math::Vector3 scale) { global.scale = scale; }
    };
}


#endif //GAMETRANSFORM_H
