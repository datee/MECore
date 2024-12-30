//
// Created by ryen on 12/23/24.
//

#include "Global.h"
#include "time/TimeGlobal.h"

HL_PRIM double HL_NAME(time_game_get_elapsed)() {
    hl_blocking(true);
    return me::time::mainGame.GetElapsed();
}

HL_PRIM double HL_NAME(time_game_get_delta)() {
    return me::time::mainGame.GetDelta();
}

HL_PRIM double HL_NAME(time_game_get_scale)() {
    return me::time::mainGame.GetScale();
}

HL_PRIM void HL_NAME(time_game_set_scale)(double value) {
    me::time::mainGame.SetScale(value);
}

HL_PRIM double HL_NAME(time_real_get_elapsed)() {
    return me::time::mainReal.GetElapsed();
}

HL_PRIM double HL_NAME(time_real_get_delta)() {
    return me::time::mainReal.GetDelta();
}

DEFINE_PRIM(_F64, time_game_get_elapsed, _NO_ARG);
DEFINE_PRIM(_F64, time_game_get_delta, _NO_ARG);
DEFINE_PRIM(_F64, time_game_get_scale, _NO_ARG);
DEFINE_PRIM(_VOID, time_game_set_scale, _F64);

DEFINE_PRIM(_F64, time_real_get_elapsed, _NO_ARG);
DEFINE_PRIM(_F64, time_real_get_delta, _NO_ARG);