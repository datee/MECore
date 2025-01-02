package me.internal.math;

import me.internal.math.BaseVec4;

// I would use the abstract types here for extra clarity but then HashLink would expect abstracts to be returned.
// While it is possible to pass in abstracts from the C side. It probably isn't worth the hassle.

/**
    C-Style Transform.
    Please use me.math.Transform.
**/
@:struct
class BaseTransform {
    @:packed public var position(default, never): BaseVec4;
    @:packed public var rotation(default, never): BaseVec4;
    @:packed public var scale(default, never): BaseVec4;

    public inline function new(pos: BaseVec4, rot: BaseVec4, sc: BaseVec4) {
        // Since they're packed, they cannot be null. So it is safe to set them.
        position.Set(pos);
        rotation.Set(rot);
        scale.Set(sc);
    }

    public inline function Copy(): BaseTransform {
        return new BaseTransform(position, rotation, scale);
    }
}
