package me.internal;

import hl.I64;

@:struct
final class UUID {
    var low: I64;
    var high: I64;

    public static function Random(): UUID {
        return null;
    }

    public function hashCode(): Int {
        return 0;
    }
}
