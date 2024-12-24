//
// Created by ryen on 12/23/24.
//

#include "Global.h"
#include "time/TimeGlobal.h"

HL_PRIM double HL_NAME(time_game_get_elapsed)() {
    return me::time::gameTime.GetElapsed();
}

HL_PRIM double HL_NAME(time_game_get_delta)() {
    return me::time::gameTime.GetDelta();
}

HL_PRIM double HL_NAME(time_game_get_scale)() {
    return me::time::gameTime.GetScale();
}

HL_PRIM void HL_NAME(time_game_set_scale)(double value) {
    me::time::gameTime.SetScale(value);
}

HL_PRIM double HL_NAME(time_real_get_elapsed)() {
    return me::time::realTime.GetElapsed();
}

HL_PRIM double HL_NAME(time_real_get_delta)() {
    return me::time::realTime.GetDelta();
}


DEFINE_PRIM(_F64, time_game_get_elapsed, _NO_ARG);
DEFINE_PRIM(_F64, time_game_get_delta, _NO_ARG);
DEFINE_PRIM(_F64, time_game_get_scale, _NO_ARG);
DEFINE_PRIM(_VOID, time_game_set_scale, _F64);
DEFINE_PRIM(_F64, time_real_get_elapsed, _NO_ARG);
DEFINE_PRIM(_F64, time_real_get_delta, _NO_ARG);