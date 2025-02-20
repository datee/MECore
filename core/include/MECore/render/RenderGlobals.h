//
// Created by ryen on 12/29/24.
//

#pragma once

#include <memory>
#include <SDL3/SDL_gpu.h>

#include "Window.h"
#include "MECore/math/Types.h"

namespace ME::render {
    inline SDL_GPUDevice* mainDevice;
    inline std::unique_ptr<Window> mainWindow;

    bool Initialize();
    void Shutdown();

    // Helper function to create a main window
    bool CreateMainWindow(const std::string& name, const IntVector2& res);
}
