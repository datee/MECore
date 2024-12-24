package me;

import me.internal.LogInterface;

/**
  * The engine's logger.
  */ 
final class Log {
    public static function Info(msg: String): Void {
        LogInterface.log_info(msg);
    }

    public static function Warning(msg: String): Void {
        LogInterface.log_warn(msg);
    }

    public static function Error(msg: String): Void {
        LogInterface.log_error(msg);
    }
}