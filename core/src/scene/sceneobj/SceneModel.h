//
// Created by ryen on 2/19/25.
//

#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include "SceneObject.h"

namespace me::scene {
    class SceneModel : public SceneObject {
        public:
        SceneModel() : SceneObject(u"me.scene.Model") {}
    };
}

#endif //SCENEMODEL_H
