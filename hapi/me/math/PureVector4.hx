package me.math;

/**
    A four-dimensional vector.
**/
@:struct
class PureVector4 {
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

    public function Set(quat: PureVector4): Void {
        x = quat.x;
        y = quat.y;
        z = quat.z;
        w = quat.w;
    }

    public function Copy(): PureVector4 {
        return new PureVector4(x, y, z, w);
    }
}
