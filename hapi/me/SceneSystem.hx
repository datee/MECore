package me;

import me.internal.Pointer;
import me.internal.SceneSystemBase;

final class SceneSystem extends SceneSystemBase {
    public static var instance: SceneSystem;

    override function ME_Initialize(ptr:Pointer) {
        super.ME_Initialize(ptr);
        instance = this;
    }
}
