package me.scene;

import me.math.Vector3;
import me.internal.bindings.SceneTransformBindings;
import me.math.Transform;
import me.internal.EngineObject;

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
