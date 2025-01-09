//
// Created by ryen on 1/8/25.
//

#include "Global.h"
#include "scene/sceneobj/SceneMesh.h"

HL_PRIM vdynamic* HL_NAME(scene_sceneobj_mesh_create)() {
    auto* mesh = new me::scene::SceneMesh("new mesh");
    return mesh->GetHaxeObject()->GetDynamic();
}

HL_PRIM vdynamic* HL_NAME(scene_sceneobj_mesh_get_mesh)(me::scene::SceneMesh* sceneMesh) {
    return sceneMesh->mesh->GetHaxeObject()->GetDynamic();
}

HL_PRIM void HL_NAME(scene_sceneobj_mesh_set_mesh)(me::scene::SceneMesh* sceneMesh, me::asset::Mesh* mesh) {
    sceneMesh->mesh = std::shared_ptr<me::asset::Mesh>(mesh);
}

DEFINE_PRIM(_DYN, scene_sceneobj_mesh_create, _NO_ARG);
DEFINE_PRIM(_DYN, scene_sceneobj_mesh_get_mesh, _PTR);
DEFINE_PRIM(_VOID, scene_sceneobj_mesh_set_mesh, _PTR _PTR);
