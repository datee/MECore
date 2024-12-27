package me;

import me.Scene;
import me.memory.Pointer;

class SceneSystem {
    static var mainSystem: SceneSystem;

    private var ptr: Pointer;
    private var cache: Map<UInt, Scene>;

    private function new(ptr: Pointer) {
        this.ptr = ptr;
    }

    function GetSceneByID(id: UInt): Scene {
        var result = cache.get(id);
        if (result != null) {
            return result;
        }

        return null;
    }
}
