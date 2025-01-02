package me.internal.math;

/**
    A four-dimensional vector.
**/
@:struct
class BaseVec4 {
    public var x: Single;
    public var y: Single;
    public var z: Single;
    public var w: Single;

    public inline function new(x: Single, y: Single, z: Single, w: Single) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.w = w;
    }

    public inline function Set(vec: BaseVec4): Void {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;
    }

    public inline function Copy(): BaseVec4 {
        return new BaseVec4(x, y, z, w);
    }
}
