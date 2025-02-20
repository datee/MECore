//
// Created by ryen on 1/2/25.
//

#pragma once

#include <string>
#include <vector>

#ifndef HAXE_INCLUDE
#define HAXE_INCLUDE
extern "C" {
    #include <hl.h>
    #include <hlmodule.h>
}
#endif

namespace ME::haxe {
    using TypeName = std::u16string;
    using FuncName = std::u16string;
    using FieldName = std::string;

    using FuncArgs = std::vector<vdynamic*>;
}
