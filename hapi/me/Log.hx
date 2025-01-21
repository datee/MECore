package me;

/**
    The engine's logger.
**/ 
final class Log {
    public static function Info(msg: String): Void {
        LogBindings.log_info(msg);
    }

    public static function Warning(msg: String): Void {
        LogBindings.log_warn(msg);
    }

    public static function Error(msg: String): Void {
        LogBindings.log_error(msg);
    }
}

@:allow(me.Log)
@:hlNative("MECore")
private extern class LogBindings {
    private static function log_info(msg: String): Void;
    private static function log_warn(msg: String): Void;
    private static function log_error(msg: String): Void;
}
