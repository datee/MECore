//
// Created by ryen on 1/21/25.
//

#include "Global.h"
#include "input/InputGlobals.h"

HL_PRIM me::math::Vector2* HL_NAME(input_mouse_delta)() {
    return &me::input::mouseDelta;
}

DEFINE_PRIM(_VECTOR2, input_mouse_delta, _NO_ARG);
