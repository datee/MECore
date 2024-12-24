//
// Created by ryen on 12/23/24.
//

#include "TimeGlobal.h"

namespace me::time {
    void Initialize() {
        gameTime = TimeSystem();
        realTime = TimeSystem();
    }

    void Update() {
        gameTime.Update();
        realTime.Update();
    }

    void Reset() {
        gameTime.Reset();
        realTime.Reset();
    }
}
