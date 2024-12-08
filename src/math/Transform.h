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

        static const Transform IDENTITY;

        [[nodiscard]] inline Vector3 Up() const;
        [[nodiscard]] inline Vector3 Right() const;
        [[nodiscard]] inline Vector3 Forward() const;

        [[nodiscard]] inline Matrix4x4 ToMatrix() const;
    };

    constexpr Transform Transform::IDENTITY {
        kmVec3{ 0.0f, 0.0f, 0.0f },
        kmQuaternion{ 0.0f, 0.0f, 0.0f, 1.0f },
        kmVec3{ 1.0f, 1.0f, 1.0f }
    };
}

#endif //TRANSFORM_H
