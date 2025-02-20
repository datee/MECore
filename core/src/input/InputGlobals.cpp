//
// Created by ryen on 1/21/25.
//

#include <SDL3/SDL_mouse.h>

#include "MECore/input/InputGlobals.h"

namespace ME::input {
    void Update() {
        SDL_GetRelativeMouseState(&mouseDelta.x, &mouseDelta.y);
    }
}
