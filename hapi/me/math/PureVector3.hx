package me.math;

/**
    A three-dimensional vector.
**/
@:struct
class PureVector3 {
    public var x: Single;
    public var y: Single;
    public var z: Single;

    public inline function new(x: Single, y: Single, z: Single) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public inline function Set(vec: PureVector3): Void {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    public inline function Copy(): PureVector3 {
        return new PureVector3(x, y, z);
    }
}
