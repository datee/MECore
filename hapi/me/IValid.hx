package me;

interface IValid {
    public var IsValid(get, never): Bool;
}

class IValidExt {
    public static function IsValidSafe(obj: IValid) {
        return obj != null && obj.IsValid;
    }
}
