package me.internal;

import me.Scene;
import me.internal.EngineObject;

class SceneSystemBase extends EngineObject {
    var cache: Map<UInt, Scene>;

    public function GetSceneWithID(id: UInt): Scene {
        return null;
    }
}
