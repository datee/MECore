package me.internal.macro;

#if macro

import haxe.macro.Compiler;
import haxe.display.Display.MetadataTarget;

class AddMeta {
    public static function Add() {
        Compiler.registerCustomMetadata({
            metadata: ":valueType",
            doc: "Makes a class act like a value type.",
            targets: [ MetadataTarget.Abstract, MetadataTarget.Class ]
        });

        Compiler.registerCustomMetadata({
            metadata: ":ref",
            doc: "Passes a value type class by reference",
            targets: [ MetadataTarget.Expr ]
        });
    }
}

#end
