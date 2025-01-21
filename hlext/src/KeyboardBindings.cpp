//
// Created by ryen on 1/21/25.
//

#include "Global.h"

#include <SDL3/SDL_keyboard.h>

HL_PRIM bool HL_NAME(input_kb_scan_pressed)(int scanCode) {
    const bool* arr = SDL_GetKeyboardState(NULL);
    return arr[scanCode];
}

DEFINE_PRIM(_BOOL, input_kb_scan_pressed, _I32);
