//
// Created by ryen on 12/23/24.
//

#pragma once

#define HL_NAME(n) MECore_##n

extern "C" {
    #include <hl.h>
}

#define _PTR _I64

#define _VECTOR2 _STRUCT
#define _VECTOR3 _STRUCT
#define _VECTOR4 _STRUCT

#define _QUAT _STRUCT

#define _TRANSFORM _STRUCT
