package me;

import me.IValid;
import me.memory.Pointer;

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
    function ME_Initialize(pointer: Pointer) {
        this.pointer = pointer;
    }
}
