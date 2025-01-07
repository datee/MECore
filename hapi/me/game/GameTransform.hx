package me.game;

import me.internal.bindings.GameTransformBindings;
import me.internal.game.GameObjectModule;
import me.math.Vector3;

final class GameTransform extends GameObjectModule {
    public var Position(get, set): Vector3;

    inline function get_Position(): Vector3 {
        return GameTransformBindings.scene_gameobj_transform_get_pos(pointer).Copy();
    }

    inline function set_Position(value: Vector3): Vector3 {
        GameTransformBindings.scene_gameobj_transform_set_pos(pointer, value);
        return value;
    }
}
