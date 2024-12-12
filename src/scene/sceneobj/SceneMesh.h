//
// Created by ryen on 12/8/24.
//

#ifndef SCENEMESH_H
#define SCENEMESH_H

#include "SceneObject.h"
#include "../../asset/Mesh.h"

namespace me::scene {
    class SceneMesh : public SceneObject {
        public:
        asset::MeshPtr mesh;
        asset::MaterialPtr material;
    };
}

#endif //SCENEMESH_H
