//
// Created by ryen on 12/5/24.
//

#ifndef RENDERPIPELINE_H
#define RENDERPIPELINE_H

#include "RenderPass.h"

namespace me::render {
    class RenderPipeline {
        public:
        RenderPipeline();
        virtual ~RenderPipeline();

        virtual void Render(scene::SceneWorld* world);
    };
}

#endif //RENDERPIPELINE_H
