//
// Created by ryen on 12/29/24.
//

#pragma once

#include "RenderInterface.h"

namespace ME::render {
    inline RenderInterface* interface;

    bool Initialize();
    void Shutdown();
}
