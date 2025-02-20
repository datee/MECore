//
// Created by ryen on 12/23/24.
//

#include "MECore/time/TimeGlobal.h"

namespace ME::time {
    void Initialize() {
        mainGame = TimeSystem();
        mainReal = TimeSystem();
    }

    void Update() {
        mainGame.Update();
        mainReal.Update();
    }

    void Reset() {
        mainGame.Reset();
        mainReal.Reset();
    }
}
