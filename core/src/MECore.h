//
// Created by ryen on 12/29/24.
//

#ifndef MECORE_H
#define MECORE_H

namespace me {
    enum class MESystems {
        None = 0,
        Log = 1,
        FS = Log << 1,
        Job = FS << 1,
        Input = Job << 1,
        Haxe = Input << 1,
        SDLRender = Haxe << 1,
        Physics = SDLRender << 1,
        Scene = Physics << 1,
        Time = Scene << 1,

        All = Log | SDLRender | Physics | FS | Scene | Time | Haxe | Input,
    };

    // Initializes specified engine subsystems
    bool Initialize(const MESystems& systems);
    void Shutdown();
}

#endif //MECORE_H
