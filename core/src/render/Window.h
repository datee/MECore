//
// Created by ryen on 12/5/24.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL_video.h>

#include "math/Types.h"

namespace me::render {
    class Window {
        private:
        SDL_Window* window;
        math::IntVector2 resolution;
        float aspect;

        Window() = default;

        public:
        ~Window();

        static Window* Create(const std::string& name, const math::IntVector2& resolution);

        // Please don't destroy it.
        [[nodiscard]] inline SDL_Window* GetWindow() const { return window; }
        [[nodiscard]] inline math::IntVector2 GetResolution() const { return resolution; }
        [[nodiscard]] inline float GetAspect() const { return aspect; }
    };
}

#endif //WINDOW_H
