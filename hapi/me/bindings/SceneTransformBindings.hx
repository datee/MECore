package me.bindings;

import me.math.PureVector3;
import me.memory.Pointer;
import me.math.PureTransform;

@:hlNative("MECore")
extern class SceneTransformBindings {
    static function scene_sceneobj_transform_get_raw(ptr: Pointer): PureTransform;
    static function scene_sceneobj_transform_set_raw(ptr: Pointer, v: PureTransform): Void;
    static function scene_sceneobj_transform_get_pos(ptr: Pointer): PureVector3;
    static function scene_sceneobj_transform_set_pos(ptr: Pointer, v: PureVector3): Void;
}
