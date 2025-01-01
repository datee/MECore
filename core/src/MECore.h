//
// Created by ryen on 12/29/24.
//

#ifndef MECORE_H
#define MECORE_H

namespace me {
    enum class MESystems {
        None = 0,
        Log = 1 << 0,
        SDLRender = 1 << 1,
        Job = 1 << 2,
        Physics = 1 << 3,
        FS = 1 << 4,
        Scene = 1 << 5,
        Time = 1 << 6,
        Haxe = 1 << 7,
        All = Log | SDLRender | Physics | FS | Scene | Time | Haxe,
    };

    // Initializes specified engine subsystems
    bool Initialize(const MESystems& systems);
    void Shutdown();
}

#endif //MECORE_H
