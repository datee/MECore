package me;

import me.bindings.LogBindings;

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