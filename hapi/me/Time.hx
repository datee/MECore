package me;

import me.internal.TimeInterface;

final class Time {
    public static var ElapsedAsDouble(get, never): Float;
    public static var DeltaAsDouble(get, never): Float;
    public static var ScaleAsDouble(get, set): Float;

    public static var Elapsed(get, never): Single;
    public static var Delta(get, never): Single;
    public static var Scale(get, set): Single;

    public static var RealElapsedAsDouble(get, never): Float;
    public static var RealDeltaAsDouble(get, never): Float;

    public static var RealElapsed(get, never): Single;
    public static var RealDelta(get, never): Single;

    // GAME TIME

    static function get_ElapsedAsDouble(): Float {
        return TimeInterface.time_game_get_elapsed();
    }

    static function get_DeltaAsDouble(): Float {
        return TimeInterface.time_game_get_delta();
    }

    static function get_ScaleAsDouble(): Float {
        return TimeInterface.time_game_get_scale();
    }

    static function set_ScaleAsDouble(value: Float): Float {
        TimeInterface.time_game_set_scale(value);
        return value;
    }

    static function get_Elapsed(): Single {
        return ElapsedAsDouble;
    }

    static function get_Delta(): Single {
        return DeltaAsDouble;
    }

    static function get_Scale(): Single {
        return ScaleAsDouble;
    }

    static function set_Scale(value: Single): Single {
        ScaleAsDouble = value;
        return value;
    }

    // REAL TIME

    static function get_RealElapsedAsDouble(): Float {
        return TimeInterface.time_real_get_elapsed();
    }

    static function get_RealDeltaAsDouble(): Float {
        return TimeInterface.time_real_get_delta();
    }

    static function get_RealElapsed(): Single {
        return RealElapsedAsDouble;
    }

    static function get_RealDelta(): Single {
        return RealDeltaAsDouble;
    }
}