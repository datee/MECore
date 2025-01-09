//
// Created by ryen on 12/8/24.
//

#ifndef SCENEMESH_H
#define SCENEMESH_H

#include "SceneObject.h"
#include "asset/Material.h"
#include "asset/Mesh.h"

namespace me::scene {
    class SceneMesh : public SceneObject {
        public:
        asset::MeshPtr mesh;
        asset::MaterialPtr material;

        SceneMesh() : SceneObject(u"me.scene.SceneMesh") {}
        explicit SceneMesh(const std::string& name) : SceneMesh() { this->name = name; }
    };
}

#endif //SCENEMESH_H
