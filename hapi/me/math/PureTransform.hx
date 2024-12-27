package me.math;

import me.math.PureVector4;
import me.math.PureVector3;
import me.math.Vector3;
import me.math.Quaternion;
/**
    C-Style Transform.
    Please use me.math.Transform.
**/
@:struct
class PureTransform {
    @:packed var position(default, never): PureVector3;
    @:packed var rotation(default, never): PureVector4;
    @:packed var scale(default, never): PureVector3;

    public var Position(get, set): Vector3;
    public var Rotation(get, set): Quaternion;
    public var Scale(get, set): Vector3;

    public inline function new(pos: PureVector3, rot: PureVector4, sc: PureVector3) {
        position.Set(pos);
        rotation.Set(rot);
        scale.Set(sc);
    }

    function get_Position(): Vector3 {
        return position.Copy();
    }

    function set_Position(vec: Vector3): Vector3 {
        position.Set(vec);
        return vec;
    }

    function get_Rotation(): Quaternion {
        return rotation.Copy();
    }

    function set_Rotation(quat: Quaternion): Quaternion {
        rotation.Set(quat);
        return quat;
    }

    function get_Scale(): Vector3 {
        return scale.Copy();
    }

    function set_Scale(vec: Vector3): Vector3 {
        scale.Set(vec);
        return vec;
    }

    public function Copy(): PureTransform {
        return new PureTransform(position, rotation, scale);
    }
}
