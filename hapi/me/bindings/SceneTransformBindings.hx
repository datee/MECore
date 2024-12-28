package me.bindings;

import me.math.BaseVec4;
import me.memory.Pointer;
import me.math.BaseTransform;

@:hlNative("MECore")
extern class SceneTransformBindings {
    static function scene_sceneobj_transform_get_raw(ptr: Pointer): BaseTransform;
    static function scene_sceneobj_transform_set_raw(ptr: Pointer, v: BaseTransform): Void;
    static function scene_sceneobj_transform_get_pos(ptr: Pointer): BaseVec4;
    static function scene_sceneobj_transform_set_pos(ptr: Pointer, v: BaseVec4): Void;
}
