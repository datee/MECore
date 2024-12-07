//
// Created by ryen on 12/5/24.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_gpu.h>

namespace me::render {
    class Window {
        private:
        SDL_Window* window;
        SDL_GPUDevice* device;

        public:
        Window(); // we should probably use a factory method since it can error
        ~Window();

        [[nodiscard]] SDL_Window* GetWindow() const;
        [[nodiscard]] SDL_GPUDevice* GetDevice() const;
    };
}

#endif //WINDOW_H
