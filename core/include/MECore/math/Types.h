//
// Created by ryen on 12/6/24.
//

#pragma once

#include <Jolt/Jolt.h>

namespace ME {
    constexpr float DEG_TO_RAD = JPH::JPH_PI / 180.0f;
    constexpr float RAD_TO_DEG = 180.0f / JPH::JPH_PI;

    // using IntVector2 = mathfu::int2;
    // using IntVector3 = mathfu::int3;
    // using IntVector4 = mathfu::int4;

    struct IntVector2 {
        int x;
        int y;
    };

    struct Vector2 {
        union {
            struct {
                float x;
                float y;
            };
            float data[4];
            JPH::Vec4 vec4;
        };
    };
    using Vector3 = JPH::Vec3;
    using PackedVector3 = JPH::Float3;
    using Vector4 = JPH::Vec4;
    using PackedVector4 = JPH::Float4;

    using Color = Vector4;
    using Quaternion = JPH::Quat;
    using Matrix4x4 = JPH::Mat44;
    using PackedMatrix4x4 = PackedVector4[4];
}
