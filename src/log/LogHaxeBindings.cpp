//
// Created by ryen on 12/22/24.
//

#define HL_NAME(n) MANIFOLD_Log_##n

#include "spdlog/spdlog.h"
#include <hl.h>

HL_PRIM void HL_NAME(Info)(vstring* msg) {
    // spdlog::info(msg->bytes);
}

DEFINE_PRIM(_VOID, Info, _STRING);
