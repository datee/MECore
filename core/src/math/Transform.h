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
        Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }

        static Transform identity;

        [[nodiscard]] inline Vector3 Right() const { return rotation * Vector3(1, 0, 0); }
        [[nodiscard]] inline Vector3 Up() const { return rotation * Vector3(0, 1, 0); }
        [[nodiscard]] inline Vector3 Forward() const { return rotation * Vector3(0, 0, 1); }

        // Localizes a point.
        [[nodiscard]] Vector3 EnterPoint(const Vector3& worldPoint) const;
        // Localizes a direction.
        [[nodiscard]] Vector3 EnterDirection(const Vector3& worldDir) const;
        // Localizes a vector.
        [[nodiscard]] Vector3 EnterVector(const Vector3& worldVector) const;
        [[nodiscard]] Quaternion EnterQuaternion(const Quaternion& worldRot) const;
        [[nodiscard]] Transform Enter(const Transform& world) const;

        // De-localizes a point. Inverse of EnterPoint
        [[nodiscard]] Vector3 ExitPoint(const Vector3& localPoint) const;
        // De-localizes a direction. Inverse of EnterDirection
        [[nodiscard]] Vector3 ExitDirection(const Vector3& localDir) const;
        // De-localizes a vector. Inverse of EnterVector
        [[nodiscard]] Vector3 ExitVector(const Vector3& localVector) const;
        [[nodiscard]] Quaternion ExitQuaternion(const Quaternion& localRot) const;
        [[nodiscard]] Transform Exit(const Transform& local) const;

        [[nodiscard]] Matrix4x4 ToTRS(bool rightHanded = false) const;
        [[nodiscard]] Matrix4x4 ToSRT(bool rightHanded = false) const;
    };

    inline Transform Transform::identity = Transform({}, Quaternion::sIdentity(), {1, 1, 1});
}

#endif //TRANSFORM_H
