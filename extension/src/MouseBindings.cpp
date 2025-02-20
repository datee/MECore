//
// Created by ryen on 1/21/25.
//

#include "Global.h"
#include "MECore/input/InputGlobals.h"

using namespace ME;
using namespace ME::input;

HL_PRIM Vector2* HL_NAME(input_mouse_delta)() {
    return &mouseDelta;
}

DEFINE_PRIM(_VECTOR2, input_mouse_delta, _NO_ARG);
