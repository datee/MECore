//
// Created by ryen on 1/2/25.
//

#include "Global.h"
#include "scene/SceneGlobals.h"

HL_PRIM vdynamic* HL_NAME(scene_system_get_main)() {
    return me::scene::mainSystem->GetHaxeObject()->GetDynamic();
}

HL_PRIM uint HL_NAME(scene_system_get_scene_count)(me::scene::SceneSystem* sceneSystem) {
    return sceneSystem->GetSceneCount();
}

HL_PRIM vdynamic* HL_NAME(scene_system_get_scene_with_id)(me::scene::SceneSystem* sceneSystem, uint id) {
    return sceneSystem->GetScene(id)->GetHaxeObject()->GetDynamic();
}

DEFINE_PRIM(_DYN, scene_system_get_main, _NO_ARG);
DEFINE_PRIM(_I32, scene_system_get_scene_count, _PTR);
DEFINE_PRIM(_DYN, scene_system_get_scene_with_id, _PTR _I32);
