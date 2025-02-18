package me.internal.macro;

#if macro

import haxe.macro.Compiler;
import haxe.display.Display.MetadataTarget;

class Metadata {
    public static function Add() {
        Compiler.registerCustomMetadata({
            metadata: ":valueType",
            doc: "Makes a class act like a value type.",
            targets: [ MetadataTarget.Abstract, MetadataTarget.Class ]
        });

        Compiler.registerCustomMetadata({
            metadata: ":ref",
            doc: "Passes a value type by reference. Does nothing to reference types.",
            targets: [ MetadataTarget.Expr ]
        });

        Compiler.registerCustomMetadata({
            metadata: ":meIgnore",
            doc: "Metadata that certain ME functions will ignore.",
            targets: [ MetadataTarget.Expr ]
        });
    }
}

#end
