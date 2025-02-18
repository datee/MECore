//
// Created by ryen on 12/22/24.
//

#include <codecvt>
#include <locale>

#include "Global.h"
#include "spdlog/spdlog.h"

HL_PRIM void HL_NAME(log_info)(vstring* msg) {
    spdlog::info(hl_to_utf8(msg->bytes));
}

HL_PRIM void HL_NAME(log_warn)(vstring* msg) {
    spdlog::warn(hl_to_utf8(msg->bytes));
}

HL_PRIM void HL_NAME(log_error)(vstring* msg) {
    spdlog::error(hl_to_utf8(msg->bytes));
}

DEFINE_PRIM(_VOID, log_info, _STRING);
DEFINE_PRIM(_VOID, log_warn, _STRING);
DEFINE_PRIM(_VOID, log_error, _STRING);
