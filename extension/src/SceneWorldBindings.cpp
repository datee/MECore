//
// Created by ryen on 1/8/25.
//

#include "Global.h"
#include "scene/sceneobj/SceneWorld.h"

HL_PRIM void HL_NAME(scene_sceneobj_world_assign)(me::scene::SceneWorld* world, me::scene::SceneObject* obj) {
    world->AddObject(obj);
}

DEFINE_PRIM(_VOID, scene_sceneobj_world_assign, _PTR _PTR)
