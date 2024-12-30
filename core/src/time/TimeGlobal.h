//
// Created by ryen on 12/23/24.
//

#ifndef TIMEGLOBAL_H
#define TIMEGLOBAL_H

#include "TimeSystem.h"

namespace me::time {
    inline TimeSystem mainGame;
    inline TimeSystem mainReal;

    void Initialize();
    void Update();
    void Reset();
}

#endif //TIMEGLOBAL_H
