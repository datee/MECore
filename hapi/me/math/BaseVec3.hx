package me.math;

// It would be cool if I could make this type generic.
// So if something requires a different type its as easy as BaseVec3<Int>.
// But that messes with the interopability with C. So it stays this way.

/**
    A three-dimensional vector.
**/
@:struct
class BaseVec3 {
    public var x: Single;
    public var y: Single;
    public var z: Single;

    public inline function new(x: Single, y: Single, z: Single) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public inline function Set(vec: BaseVec3): Void {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    public inline function Copy(): BaseVec3 {
        return new BaseVec3(x, y, z);
    }
}
