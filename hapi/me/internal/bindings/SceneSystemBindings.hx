package me.internal.bindings;

import me.Scene;
import me.internal.SceneSystemBase;
import me.internal.Pointer;

@:hlNative("MECore")
extern class SceneSystemBindings {
    // static function scene_system_get_main(): SceneSystemBase;
    static function scene_system_get_scene_count(ptr: Pointer): UInt;
    static function scene_system_get_scene_with_id(ptr: Pointer, id: UInt): Dynamic;
}
