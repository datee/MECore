//
// Created by ryen on 12/26/24.
//

#include "Global.h"
#include "math/Transform.h"
#include "scene/gameobj/GameTransform.h"

// Haxe expects pointers to be returned. They are copied on the Haxe side.

HL_PRIM me::math::Transform* HL_NAME(scene_gameobj_transform_get_raw)(me::scene::GameTransform* ptr) {
    return &ptr->GlobalRaw();
}

HL_PRIM void HL_NAME(scene_gameobj_transform_set_raw)(me::scene::GameTransform* ptr, const me::math::Transform* value) {
    auto transform = ptr->GlobalRaw();
    transform.position = value->position;
    transform.rotation = value->rotation;
    transform.scale = value->scale;
}

HL_PRIM me::math::Vector3* HL_NAME(scene_gameobj_transform_get_pos)(me::scene::GameTransform* ptr) {
    return &ptr->GlobalRaw().position;
}

HL_PRIM void HL_NAME(scene_gameobj_transform_set_pos)(me::scene::GameTransform* ptr, const me::math::Vector3* value) {
    ptr->SetGlobalPosition(*value);
}

DEFINE_PRIM(_TRANSFORM, scene_gameobj_transform_get_raw, _PTR);
DEFINE_PRIM(_VOID, scene_gameobj_transform_set_raw, _PTR _TRANSFORM);
DEFINE_PRIM(_VECTOR3, scene_gameobj_transform_get_pos, _PTR);
DEFINE_PRIM(_VOID, scene_gameobj_transform_set_pos, _PTR _VECTOR3);
