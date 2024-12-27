package me.math;

import me.math.PureVector4;

@:notNull
@:forward(x, y, z, w)
abstract Quaternion(PureVector4) from PureVector4 to PureVector4 {
    public inline function new(x: Single, y: Single, z: Single, w: Single) {
        this = new PureVector4(x, y, z, w);
    }

    public inline static function Identity(): Quaternion {
        return new Quaternion(0, 0, 0, 1);
    }
}
