package me.scene;

import me.math.Vector3;
import me.math.Transform;
import me.internal.EngineObject;
import me.internal.math.BaseVec4;
import me.internal.Pointer;
import me.internal.math.BaseTransform;

final class SceneTransform extends EngineObject {
    public var Raw(get, set): Transform;
    public var Position(get, set): Vector3;

    inline function get_Raw(): Transform {
        return SceneTransformBindings.scene_sceneobj_transform_get_raw(pointer).Copy();
    }

    inline function set_Raw(value: Transform): Transform {
        SceneTransformBindings.scene_sceneobj_transform_set_raw(pointer, value);
        return value;
    }

    inline function get_Position(): Vector3 {
        return SceneTransformBindings.scene_sceneobj_transform_get_pos(pointer).Copy();
    }

    inline function set_Position(value: Vector3): Vector3 {
        SceneTransformBindings.scene_sceneobj_transform_set_pos(pointer, value);
        return value;
    }
}

@:allow(me.scene.SceneTransform)
@:hlNative("MECore")
private extern class SceneTransformBindings {
    private static function scene_sceneobj_transform_get_raw(ptr: Pointer): BaseTransform;
    private static function scene_sceneobj_transform_set_raw(ptr: Pointer, v: BaseTransform): Void;
    private static function scene_sceneobj_transform_get_pos(ptr: Pointer): BaseVec4;
    private static function scene_sceneobj_transform_set_pos(ptr: Pointer, v: BaseVec4): Void;
}
