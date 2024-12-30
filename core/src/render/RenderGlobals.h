//
// Created by ryen on 12/29/24.
//

#ifndef RENDERGLOBALS_H
#define RENDERGLOBALS_H
#include <memory>
#include <SDL3/SDL_gpu.h>

#include "Window.h"
#include "math/Types.h"

namespace me::render {
    inline SDL_GPUDevice* mainDevice;
    inline std::unique_ptr<Window> mainWindow;

    bool Initialize();
    void Shutdown();

    // Helper function to create a main window
    bool CreateMainWindow(const std::string& name, const math::IntVector2& res);
}

#endif //RENDERGLOBALS_H
