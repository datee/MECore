//
// Created by ryen on 2/24/25.
//

#pragma once

#include "RenderNode.h"
#include "MECore/math/Types.h"

namespace ME::node {
    class RenderCamera final : public RenderNode {
        private:
        float fieldOfView;
        float zNear;
        float zFar;

        bool usingCustomProjection;
        Matrix4x4 projectionMatrix;

        // Regenerates the projection matrix using this camera's FOV.
        void RegenerateMatrix();

        public:
        RenderCamera();

        inline float GetFOV() const { return fieldOfView; }
        inline Matrix4x4 GetProjectionMatrix() const { return projectionMatrix; }

        inline void SetFOV(float value) { fieldOfView = value;  }
    };
}
