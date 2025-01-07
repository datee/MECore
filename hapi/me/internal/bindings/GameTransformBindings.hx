package me.internal.bindings;

import me.internal.math.BaseVec4;
import me.internal.Pointer;
import me.internal.math.BaseTransform;

@:hlNative("MECore")
extern class GameTransformBindings {
    static function scene_gameobj_transform_get_raw(ptr: Pointer): BaseTransform;
    static function scene_gameobj_transform_set_raw(ptr: Pointer, v: BaseTransform): Void;
    static function scene_gameobj_transform_get_pos(ptr: Pointer): BaseVec4;
    static function scene_gameobj_transform_set_pos(ptr: Pointer, v: BaseVec4): Void;
}
