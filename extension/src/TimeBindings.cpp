//
// Created by ryen on 12/23/24.
//

#include "Global.h"
#include "MECore/time/TimeGlobal.h"

using namespace ME::time;

HL_PRIM double HL_NAME(time_game_get_elapsed)() {
    hl_blocking(true);
    return mainGame.GetElapsed();
}

HL_PRIM double HL_NAME(time_game_get_delta)() {
    return mainGame.GetDelta();
}

HL_PRIM double HL_NAME(time_game_get_scale)() {
    return mainGame.GetScale();
}

HL_PRIM void HL_NAME(time_game_set_scale)(double value) {
    mainGame.SetScale(value);
}

HL_PRIM double HL_NAME(time_real_get_elapsed)() {
    return mainReal.GetElapsed();
}

HL_PRIM double HL_NAME(time_real_get_delta)() {
    return mainReal.GetDelta();
}

DEFINE_PRIM(_F64, time_game_get_elapsed, _NO_ARG);
DEFINE_PRIM(_F64, time_game_get_delta, _NO_ARG);
DEFINE_PRIM(_F64, time_game_get_scale, _NO_ARG);
DEFINE_PRIM(_VOID, time_game_set_scale, _F64);

DEFINE_PRIM(_F64, time_real_get_elapsed, _NO_ARG);
DEFINE_PRIM(_F64, time_real_get_delta, _NO_ARG);