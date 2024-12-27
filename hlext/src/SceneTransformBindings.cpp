//
// Created by ryen on 12/26/24.
//

#include "Global.h"
#include "math/Transform.h"
#include "scene/sceneobj/SceneTransform.h"
#include "spdlog/spdlog.h"

// Haxe expects pointers to be returned. They are copied on the Haxe side.

HL_PRIM me::math::Transform* HL_NAME(scene_sceneobj_transform_get_raw)(me::scene::SceneTransform* ptr) {
    return &ptr->Raw();
}

HL_PRIM void HL_NAME(scene_sceneobj_transform_set_raw)(me::scene::SceneTransform* ptr, const me::math::Transform* value) {
    auto transform = ptr->Raw();
    transform.position = value->position;
    transform.rotation = value->rotation;
    transform.scale = value->scale;
}

HL_PRIM me::math::Vector3* HL_NAME(scene_sceneobj_transform_get_pos)(me::scene::SceneTransform* ptr) {
    return &ptr->Raw().position;
}

HL_PRIM void HL_NAME(scene_sceneobj_transform_set_pos)(me::scene::SceneTransform* ptr, const me::math::Vector3* value) {
    ptr->SetPosition(*value);
}

DEFINE_PRIM(_STRUCT, scene_sceneobj_transform_get_raw, _PTR);
DEFINE_PRIM(_VOID, scene_sceneobj_transform_set_raw, _PTR _STRUCT);
DEFINE_PRIM(_STRUCT, scene_sceneobj_transform_get_pos, _PTR);
DEFINE_PRIM(_VOID, scene_sceneobj_transform_set_pos, _PTR _STRUCT);
