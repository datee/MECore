package me.input;

enum abstract ScanCode(Int) to Int {
    var Unknown = 0;

    var A = 4;
    var B = 5;
    var C = 6;
    var D = 7;
    var E = 8;
    var F = 9;
    var G = 10;
    var H = 11;
    var I = 12;
    var J = 13;
    var K = 14;
    var L = 15;
    var M = 16;
    var N = 17;
    var O = 18;
    var P = 19;
    var Q = 20;
    var R = 21;
    var S = 22;
    var T = 23;
    var U = 24;
    var V = 25;
    var W = 26;
    var X = 27;
    var Y = 28;
    var Z = 29;

    var Alpha1 = 30;
    var Alpha2 = 31;
    var Alpha3 = 32;
    var Alpha4 = 33;
    var Alpha5 = 34;
    var Alpha6 = 35;
    var Alpha7 = 36;
    var Alpha8 = 37;
    var Alpha9 = 38;
    var Alpha0 = 39;

    var Return = 40;
    var Escape = 41;
    var Backspace = 42;
    var Tab = 43;
    var Space = 44;

    var Minus = 45;
    var Equals = 46;
    var LeftBracket = 47;
    var RightBracket = 48;
    var Backslash = 49;
    var NonUSHash = 50;
    var Semicolon = 51;
    var Apostrophe = 52;
    var Grave = 53;
    var Comma = 54;
    var Period = 55;
    var Slash = 56;

    var CapsLock = 57;

    var F1 = 58;
    var F2 = 59;
    var F3 = 60;
    var F4 = 61;
    var F5 = 62;
    var F6 = 63;
    var F7 = 64;
    var F8 = 65;
    var F9 = 66;
    var F10 = 67;
    var F11 = 68;
    var F12 = 69;
}

final class Keyboard {
    public static function ScanPressed(code: ScanCode): Bool {
        return KeyboardBindings.input_kb_scan_pressed(code);
    }
}

@:noDoc
@:allow(me.input.Keyboard)
@:hlNative("MECore")
private extern class KeyboardBindings {
    private static function input_kb_scan_pressed(scanCode: Int): Bool;
}
