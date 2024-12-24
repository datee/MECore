package me.internal;

@:allow(me)
@:hlNative("MECore")
extern class LogInterface {
    static function log_info(msg: String): Void;
    static function log_warn(msg: String): Void;
    static function log_error(msg: String): Void;
}
