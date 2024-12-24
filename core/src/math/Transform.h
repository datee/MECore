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

        Transform() = default;
        Transform(const Vector3 &position, const Quaternion &rotation, const Vector3 &scale) {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }

        static Transform identity;

        [[nodiscard]] inline Vector3 Up() const { return rotation * mathfu::kAxisY3f; }
        [[nodiscard]] inline Vector3 Right() const { return rotation * mathfu::kAxisX3f; }
        [[nodiscard]] inline Vector3 Forward() const { return rotation * mathfu::kAxisZ3f; }

        [[nodiscard]] inline Matrix4x4 ToTRS(const bool rightHanded = false) const {
            auto posPrime = position;
            posPrime *= (rightHanded ? -1.f : 1.f);
            return Matrix4x4::Transform(posPrime, rotation.ToMatrix(), scale);
        }
        [[nodiscard]] inline Matrix4x4 ToSRT(const bool rightHanded = false) const {
            auto posPrime = position;
            posPrime *= (rightHanded ? -1.f : 1.f);
            return Matrix4x4::FromScaleVector(scale) * Matrix4x4::FromRotationMatrix(rotation.ToMatrix()) * Matrix4x4::FromTranslationVector(position);
        }
    };

    inline Transform Transform::identity = Transform(mathfu::kZeros3f, Quaternion::identity, mathfu::kOnes3f);
}

#endif //TRANSFORM_H
