package me;

interface IValid {
    /**
        Is this object valid?
    **/
    public var IsValid(get, never): Bool;
}

class IValidExt {
    public static function IsValidSafe(obj: IValid) {
        return obj != null && obj.IsValid;
    }
}
