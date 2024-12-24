//
// Created by ryen on 12/22/24.
//

#include <codecvt>
#include <locale>

#include "Global.h"
#include "spdlog/spdlog.h"

inline std::string ToU8(vstring* msg) {
    std::u16string source = std::u16string(msg->bytes, msg->length);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    return converter.to_bytes(source);
}

HL_PRIM void HL_NAME(log_info)(vstring* msg) {
    spdlog::info(ToU8(msg));
}

HL_PRIM void HL_NAME(log_warn)(vstring* msg) {
    spdlog::warn(ToU8(msg));
}

HL_PRIM void HL_NAME(log_error)(vstring* msg) {
    spdlog::error(ToU8(msg));
}

DEFINE_PRIM(_VOID, log_info, _STRING);
DEFINE_PRIM(_VOID, log_warn, _STRING);
DEFINE_PRIM(_VOID, log_error, _STRING);
