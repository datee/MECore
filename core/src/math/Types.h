//
// Created by ryen on 12/6/24.
//

#ifndef TYPES_H
#define TYPES_H

#include "mathfu/constants.h"
#include "mathfu/quaternion.h"
#include "mathfu/hlsl_mappings.h"

namespace me::math {
    typedef mathfu::int2 IntVector2;
    typedef mathfu::int3 IntVector3;
    typedef mathfu::int4 IntVector4;

    typedef mathfu::float2 Vector2;
    typedef mathfu::float3 Vector3;
    typedef mathfu::VectorPacked<float, 3> PackedVector3;
    typedef mathfu::float4 Vector4;
    typedef mathfu::VectorPacked<float, 4> PackedVector4;

    typedef mathfu::float4 Color;
    typedef mathfu::Quaternion<float> Quaternion;
    typedef mathfu::float4x4 Matrix4x4;
    typedef PackedVector4 PackedMatrix4x4[4];

    constexpr int VEC2_SIZE = sizeof(float) * 2;
    constexpr int VEC3_SIZE = sizeof(float) * 3;
    constexpr int VEC4_SIZE = sizeof(float) * 4;
}

#endif //TYPES_H
