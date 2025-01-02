//
// Created by ryen on 12/6/24.
//

#ifndef TYPES_H
#define TYPES_H

#include <Jolt/Jolt.h>
#include <Jolt/Math/Vec3.h>

#include "mathfu/constants.h"
#include "mathfu/quaternion.h"
#include "mathfu/hlsl_mappings.h"

namespace me::math {
    using IntVector2 = mathfu::int2;
    using IntVector3 = mathfu::int3;
    using IntVector4 = mathfu::int4;

    using Vector2 = mathfu::float2;
    using Vector3 = mathfu::float3;
    using PackedVector3 = mathfu::VectorPacked<float, 3>;
    using Vector4 = mathfu::float4;
    using PackedVector4 = mathfu::VectorPacked<float, 4>;

    using Color = mathfu::float4;
    using Quaternion = mathfu::Quaternion<float>;
    using Matrix4x4 = mathfu::float4x4;
    using PackedMatrix4x4 = PackedVector4[4];
}

#endif //TYPES_H
