package me.math;

import me.internal.math.BaseVec4;

@:notNull
@:forward(x, y, z, w, Set, Copy)
@:forward.new
abstract Quaternion(BaseVec4) from BaseVec4 to BaseVec4 {
    public inline static function Identity(): Quaternion {
        return new Quaternion(0, 0, 0, 1);
    }

    @:op(A * B)
    public inline function MulQuat(rhs: Quaternion): Quaternion {
        return QuaternionBindings.math_quat_mul_quat(this, rhs);
    }

    @:op(A * B)
    public inline function MulVec(vec: Vector3): Vector3 {
        return QuaternionBindings.math_quat_mul_vec(this, vec);
    }

    @:from
    public static inline function FromEuler(angles: Angles): Quaternion {
        return QuaternionBindings.math_quat_from_euler(angles);
    }
}

@:allow(me.math.Quaternion)
@:hlNative("MECore")
private extern class QuaternionBindings {
    // These all return new values, do not copy.
    static function math_quat_from_euler(vec: BaseVec4): BaseVec4;
    static function math_quat_mul_quat(lhs: BaseVec4, rhs: BaseVec4): BaseVec4;
    static function math_quat_mul_vec(quat: BaseVec4, vec: BaseVec4): BaseVec4;
}
