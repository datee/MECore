//
// Created by ryen on 12/23/24.
//

#ifndef TIMEGLOBAL_H
#define TIMEGLOBAL_H

#include "TimeSystem.h"

namespace me::time {
    inline TimeSystem gameTime;
    inline TimeSystem realTime;

    void Initialize();
    void Update();
    void Reset();
}

#endif //TIMEGLOBAL_H
