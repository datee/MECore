package me.math;

/**
    A three-dimensional vector.
**/
@:struct
class BaseVec3<T> {
    public var x: T;
    public var y: T;
    public var z: T;

    public inline function new(x: T, y: T, z: T) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public inline function Set(vec: BaseVec3<T>): Void {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    public inline function Copy(): BaseVec3<T> {
        return new BaseVec3<T>(x, y, z);
    }
}
