//
// Created by ryen on 1/21/25.
//

#include "Global.h"
#include "MECore/math/Types.h"

using namespace ME;

HL_PRIM Quaternion* HL_NAME(math_quat_from_euler)(Vector3* angles) {
    return new Quaternion(Quaternion::sEulerAngles((*angles) * DEG_TO_RAD));
}

HL_PRIM Quaternion* HL_NAME(math_quat_mul_quat)(Quaternion* lhs, Quaternion* rhs) {
    return new Quaternion(*lhs * *rhs);
}

HL_PRIM Vector3* HL_NAME(math_quat_mul_vec)(Quaternion* quat, Vector3* vec) {
    return new Vector3(*quat * *vec);
}

DEFINE_PRIM(_QUAT, math_quat_from_euler, _VECTOR3);
DEFINE_PRIM(_QUAT, math_quat_mul_quat, _QUAT _QUAT);
DEFINE_PRIM(_VECTOR3, math_quat_mul_vec, _QUAT _VECTOR3);
