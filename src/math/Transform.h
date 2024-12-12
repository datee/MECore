//
// Created by ryen on 12/4/24.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Types.h"

namespace me::math {
    struct Transform {
        Vector3 position;
        Quaternion rotation;
        Vector3 scale;

        Transform() { }
        Transform(const Vector3 &position, const Quaternion &rotation, const Vector3 &scale) {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }

        static Transform identity;

        [[nodiscard]] inline Vector3 Up() const { return rotation * mathfu::kAxisY3f; }
        [[nodiscard]] inline Vector3 Right() const { return rotation * mathfu::kAxisX3f; }
        [[nodiscard]] inline Vector3 Forward() const { return rotation * mathfu::kAxisZ3f; }

        [[nodiscard]] inline Matrix4x4 ToMatrix() const {
            return Matrix4x4::Transform(position, rotation.ToMatrix(), scale);
        }
    };

    inline Transform Transform::identity = Transform(mathfu::kZeros3f, Quaternion::identity, mathfu::kOnes3f);
}

#endif //TRANSFORM_H
