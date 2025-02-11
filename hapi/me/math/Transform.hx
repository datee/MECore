package me.math;

import me.math.Vector3;
import me.math.Quaternion;
import me.internal.math.BaseTransform;

@:forward(Copy)
abstract Transform(BaseTransform) from BaseTransform to BaseTransform {
    public var Position(get, set): Vector3;
    public var Rotation(get, set): Quaternion;
    public var Scale(get, set): Vector3;

    public inline function new(position: Vector3, rotation: Quaternion, scale: Vector3) {
        this = new BaseTransform(position, rotation, scale);
    }

    public static inline function Identity(): Transform {
        return new Transform(Vector3.Zero(), Quaternion.Identity(), Vector3.One());
    }

    inline function get_Position(): Vector3 {
        return this.position.Copy();
    }

    inline function set_Position(vec: Vector3): Vector3 {
        this.position.Set(vec);
        return vec;
    }

    inline function get_Rotation(): Quaternion {
        return this.rotation.Copy();
    }

    inline function set_Rotation(quat: Quaternion): Quaternion {
        this.rotation.Set(quat);
        return quat;
    }

    inline function get_Scale(): Vector3 {
        return this.scale.Copy();
    }

    inline function set_Scale(vec: Vector3): Vector3 {
        this.scale.Set(vec);
        return vec;
    }
}
