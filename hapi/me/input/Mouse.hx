package me.input;

import me.math.Vector2;
import me.internal.math.BaseVec4;

final class Mouse {
    public static var Delta(get, never): Vector2;

    static inline function get_Delta(): Vector2 {
        return MouseBindings.input_mouse_delta().Copy();
    }
}

@:noDoc
@:allow(me.input.Mouse)
@:hlNative("MECore")
private extern class MouseBindings {
    private static function input_mouse_delta(): BaseVec4;
}
