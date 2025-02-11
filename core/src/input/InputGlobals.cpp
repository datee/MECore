//
// Created by ryen on 1/21/25.
//

#include "InputGlobals.h"

#include <SDL3/SDL_mouse.h>

namespace me::input {
    void Update() {
        SDL_GetRelativeMouseState(&mouseDelta.x, &mouseDelta.y);
    }
}
