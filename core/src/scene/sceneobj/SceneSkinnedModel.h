//
// Created by ryen on 2/19/25.
//

#ifndef SCENESKINNEDMODEL_H
#define SCENESKINNEDMODEL_H

#include "SceneModel.h"

namespace me::scene {
    class SceneSkinnedModel : public SceneObject {
        public:
        SceneSkinnedModel() : SceneObject(u"me.scene.SkinnedModel") {}
    };
}

#endif //SCENESKINNEDMODEL_H
