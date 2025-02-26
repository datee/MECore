//
// Created by ryen on 2/25/25.
//

#pragma once

namespace ME::render {
    class Viewport {
        public:
        virtual ~Viewport() = default;

        virtual void GetSize(int* width, int* height) const = 0;
        float GetAspect() const {
            int width, height;
            GetSize(&width, &height);
            return static_cast<float>(width) / static_cast<float>(height);
        }
    };
}
