package me.internal.bindings;

@:allow(me)
@:hlNative("MECore")
extern class TimeBindings {
    public static function time_game_get_elapsed(): Float;
    public static function time_game_get_delta(): Float;
    public static function time_game_get_scale(): Float;
    public static function time_game_set_scale(scale: Float): Void;

    public static function time_real_get_elapsed(): Float;
    public static function time_real_get_delta(): Float;
}
