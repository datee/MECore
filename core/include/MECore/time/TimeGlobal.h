//
// Created by ryen on 12/23/24.
//

#pragma once

#include "TimeSystem.h"

namespace ME::time {
    inline TimeSystem mainGame;
    inline TimeSystem mainReal;

    void Initialize();
    void Update();
    void Reset();
}
