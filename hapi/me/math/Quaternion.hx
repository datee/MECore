package me.math;

import me.math.BaseVec4;

@:notNull
@:forward(x, y, z, w, Set, Copy)
@:forward.new
abstract Quaternion(BaseVec4) from BaseVec4 to BaseVec4 {
    public inline static function Identity(): Quaternion {
        return new Quaternion(0, 0, 0, 1);
    }
}
