//
// Created by ryen on 12/6/24.
//

#ifndef TYPES_H
#define TYPES_H

#include "kazmath/kazmath.h"

namespace me::math {
    struct IntVector2 {
        int32_t x, y;
    };

    struct IntVector3 {
        int32_t x, y, z;
    };

    struct IntVector4 {
        int32_t x, y, z, w;
    };

    typedef kmVec2 Vector2;
    typedef kmVec3 Vector3;
    typedef kmVec4 Vector4;
    typedef kmVec4 Color;
    typedef kmQuaternion Quaternion;
    typedef kmMat4 Matrix4x4;
}

#endif //TYPES_H
