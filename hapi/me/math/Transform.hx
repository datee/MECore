package me.math;

import me.math.Vector3;
import me.math.Quaternion;
import me.math.PureTransform;

@:forward(Position, Rotation, Scale)
abstract Transform(PureTransform) from PureTransform to PureTransform {
    public inline function new(pos: Vector3, rot: Quaternion, scale: Vector3) {
        this = new PureTransform(pos, rot, scale);
    }

    public static inline function Identity(): Transform {
        return new Transform(Vector3.Zero(), Quaternion.Identity(), Vector3.One());
    }
}
