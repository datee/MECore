//
// Created by ryen on 12/5/24.
//

#pragma once

#include <SDL3/SDL_video.h>

#include "MECore/math/Types.h"

namespace ME::render {
    class Window {
        private:
        SDL_Window* window;
        IntVector2 resolution;
        float aspect;

        Window() = default;

        public:
        ~Window();

        static Window* Create(const std::string& name, const IntVector2& resolution);

        // Please don't destroy it.
        [[nodiscard]] inline SDL_Window* GetWindow() const { return window; }
        [[nodiscard]] inline IntVector2 GetResolution() const { return resolution; }
        [[nodiscard]] inline float GetAspect() const { return aspect; }
    };
}
