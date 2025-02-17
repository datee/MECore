package me;

/**
    The engine's logger.
**/ 
final class Log {
    public static function Info(msg: Dynamic): Void {
        LogBindings.log_info(Std.string(msg));
    }

    public static function Warning(msg: Dynamic): Void {
        LogBindings.log_warn(Std.string(msg));
    }

    public static function Error(msg: Dynamic): Void {
        LogBindings.log_error(Std.string(msg));
    }
}

@:allow(me.Log)
@:hlNative("MECore")
private extern class LogBindings {
    private static function log_info(msg: String): Void;
    private static function log_warn(msg: String): Void;
    private static function log_error(msg: String): Void;
}
