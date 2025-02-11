package me.math;

import me.internal.math.BaseVec4;

@:notNull
abstract Angles(BaseVec4) from BaseVec4 to BaseVec4 {
    public var Pitch(get, set): Single;
    public var Yaw(get, set): Single;
    public var Roll(get, set): Single;

    public inline function new(pitch: Single = 0, yaw: Single = 0, roll: Single = 0) {
        this = new BaseVec4(pitch, yaw, roll, 1);
    }

    inline function get_Pitch(): Single {
        return this.x;
    }

    inline function set_Pitch(v: Single): Single {
        return this.x = v;
    }

    inline function get_Yaw(): Single {
        return this.y;
    }

    inline function set_Yaw(v: Single): Single {
        return this.y = v;
    }

    inline function get_Roll(): Single {
        return this.z;
    }

    inline function set_Roll(v: Single): Single {
        return this.z = v;
    }
}
