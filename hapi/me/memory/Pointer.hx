package me.memory;

import haxe.Int64;
import hl.I64;

abstract Pointer(I64) to I64 {
    public static inline function Null(): Pointer {
        return cast 0;
    }

    public inline function IsNull(): Bool {
        return this == 0;
    }

    @:to
    public function ToString(): String {
        var other:Int64 = cast this;
        return "0x" + StringTools.hex(other.low) + StringTools.hex(other.high);
    }
}
