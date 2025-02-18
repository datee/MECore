//
// Created by ryen on 12/26/24.
//

#include "Global.h"
#include "math/Transform.h"
#include "scene/gameobj/GameTransform.h"

using namespace me::scene;
using namespace me::math;

// Haxe expects pointers to be returned. They are copied on the Haxe side.

HL_PRIM Transform* HL_NAME(scene_gameobj_transform_get_raw)(GameTransform* ptr) {
    return &ptr->GlobalRaw();
}

HL_PRIM void HL_NAME(scene_gameobj_transform_set_raw)(GameTransform* ptr, const Transform* value) {
    auto transform = ptr->GlobalRaw();
    transform.position = value->position;
    transform.rotation = value->rotation;
    transform.scale = value->scale;
}

HL_PRIM Vector3* HL_NAME(scene_gameobj_transform_get_pos)(GameTransform* ptr) {
    return &ptr->GlobalRaw().position;
}

HL_PRIM void HL_NAME(scene_gameobj_transform_set_pos)(GameTransform* ptr, const Vector3* value) {
    ptr->SetGlobalPosition(*value);
}

HL_PRIM Quaternion* HL_NAME(scene_gameobj_transform_get_rot)(GameTransform* ptr) {
    return &ptr->GlobalRaw().rotation;
}

HL_PRIM void HL_NAME(scene_gameobj_transform_set_rot)(GameTransform* ptr, const Quaternion* value) {
    ptr->SetGlobalRotation(*value);
}

DEFINE_PRIM(_TRANSFORM, scene_gameobj_transform_get_raw, _PTR);
DEFINE_PRIM(_VOID, scene_gameobj_transform_set_raw, _PTR _TRANSFORM);
DEFINE_PRIM(_VECTOR3, scene_gameobj_transform_get_pos, _PTR);
DEFINE_PRIM(_VOID, scene_gameobj_transform_set_pos, _PTR _VECTOR3);
DEFINE_PRIM(_QUAT, scene_gameobj_transform_get_rot, _PTR);
DEFINE_PRIM(_VOID, scene_gameobj_transform_set_rot, _PTR _QUAT);
