//
// Created by ryen on 12/22/24.
//

#include <codecvt>
#include <locale>

#include "Global.h"
#include "spdlog/spdlog.h"

HL_PRIM void HL_NAME(info)(vstring* msg) {
    std::u16string source = std::u16string(msg->bytes, msg->length);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    std::string dest = converter.to_bytes(source);

    spdlog::info(dest);
    // spdlog::info("haxe info called");
}

DEFINE_PRIM(_VOID, info, _STRING);
