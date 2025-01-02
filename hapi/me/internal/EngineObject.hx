package me.internal;

import me.IValid;
import me.internal.Pointer;

/**
    An object controlled by the engine.
**/
abstract class EngineObject implements IValid {
    @:allow(me)
    var pointer: Pointer;

    public var IsValid(get, never): Bool;

    @:allow(me)
    private function new(pointer: Pointer) {
        ME_Initialize(pointer);
    }

    function get_IsValid(): Bool {
        return pointer.IsNull();
    }

    /**
        When allocated by the engine, the constructor is skipped.
        This will circumvent that.
    **/
    function ME_Initialize(pointer: Pointer): Void {
        this.pointer = pointer;
    }

    /**
        Called when the object is destroyed on the C side.
        Invalidates this object.
    **/
    function ME_Destroy(): Void {
        this.pointer = Pointer.Null();
    }
}
