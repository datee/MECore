package me.internal;

import me.internal.Pointer;
import me.Scene;
import me.internal.EngineObject;

abstract class SceneSystemBase extends EngineObject {
    var cache: Map<UInt, Scene>;

    public var SceneCount(get, never): UInt;

    function get_SceneCount(): UInt {
        return SceneSystemBindings.scene_system_get_scene_count(pointer);
    }

    override function ME_Initialize(ptr: Pointer) {
        super.ME_Initialize(ptr);
        cache = new Map<UInt, Scene>();
    }

    public function GetSceneWithID(id: UInt): Scene {
        var result = cast(SceneSystemBindings.scene_system_get_scene_with_id(pointer, id), Scene);
        if (result == null) return null;
        
        cache[id] = result;
        return result;
    }
}

@:allow(me.internal.SceneSystemBase)
@:hlNative("MECore")
private extern class SceneSystemBindings {
    // static function scene_system_get_main(): SceneSystemBase;
    private static function scene_system_get_scene_count(ptr: Pointer): UInt;
    private static function scene_system_get_scene_with_id(ptr: Pointer, id: UInt): Dynamic;
}
