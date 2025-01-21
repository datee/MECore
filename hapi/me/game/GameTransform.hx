package me.game;

import me.math.Transform;
import me.internal.game.GameObjectModule;
import me.math.Vector3;
import me.internal.math.BaseVec4;
import me.internal.Pointer;
import me.internal.math.BaseTransform;


final class GameTransform extends GameObjectModule {
    public var World(get, set): Transform;
    public var Position(get, set): Vector3;

    inline function get_World(): Transform {
        return GameTransformBindings.scene_gameobj_transform_get_raw(pointer).Copy();
    }

    inline function set_World(value: Transform): Transform {
        GameTransformBindings.scene_gameobj_transform_set_raw(pointer, value);
        return value;
    }

    inline function get_Position(): Vector3 {
        return GameTransformBindings.scene_gameobj_transform_get_pos(pointer).Copy();
    }

    inline function set_Position(value: Vector3): Vector3 {
        GameTransformBindings.scene_gameobj_transform_set_pos(pointer, value);
        return value;
    }
}

@:allow(me.game.GameTransform)
@:hlNative("MECore")
private extern class GameTransformBindings {
    private static function scene_gameobj_transform_get_raw(ptr: Pointer): BaseTransform;
    private static function scene_gameobj_transform_set_raw(ptr: Pointer, v: BaseTransform): Void;
    private static function scene_gameobj_transform_get_pos(ptr: Pointer): BaseVec4;
    private static function scene_gameobj_transform_set_pos(ptr: Pointer, v: BaseVec4): Void;
}
