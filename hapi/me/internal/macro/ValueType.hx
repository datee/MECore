package me.internal.macro;

#if macro

import haxe.macro.Type;
import haxe.macro.TypeTools;
import haxe.macro.Context;
import haxe.macro.Compiler;
import haxe.macro.ComplexTypeTools;
import haxe.macro.Expr.Metadata;
import haxe.macro.Expr.ComplexType;
import haxe.macro.Expr.Function;
import haxe.macro.Expr.ExprDef;

// Made with help from SomeRanDev and PXshadow.
// seriously i wouldve stopped using this language if it werent for you guys.

// Add write check in function arg copies
// if there are no writes ever to a value arg we can skip its copy

class ValueType {
    static final VALUE_META: String = ":valueType";
    static final REF_META: String = ":ref";
    static final IGNORE_META: Array<String> = [":hlNative", ":meIgnore"];

    static var debugLogging: Bool;

    public static function Init(?list: Bool = false, ?debug: Bool = false) {
        debugLogging = debug;

        if (list) {
            Context.onAfterTyping(ListValueTypes);
        }
		Compiler.addGlobalMetadata("", "@:build(me.internal.macro.ValueType.BuildProcess())");
	}

    public static function BuildProcess() {
        final localClass = Context.getLocalClass();
        if (localClass != null) {
            if (AccessorHasAnyIgnored(localClass.get().meta)) {
                if (debugLogging) {
                    trace('Class ${localClass.toString()} ignored!');
                }
                return null;
            }
        }

        final fields = Context.getBuildFields();
        for (field in fields) {
            if (MetadataHasAnyIgnored(field.meta)) continue;

            switch (field.kind) {
                case FFun(func) if (func.expr != null): {
                    AddAssignCopies(func);
                    AddArgCopies(func);
                }
                default:
            }
        }

        return fields;
    }

    
    static function AddArgCopies(func: Function): Bool {
        final argsToCopy = [];

        // Resolve args to copy
        for (arg in func.args) {
            if (arg.type == null) continue;
            if (MetadataIsRef(arg.meta)) continue;
            if (!IsValueType(arg.type)) continue;
            argsToCopy.push(arg.name);
        }

        if (argsToCopy.length <= 0) return false;

        final initExprs = argsToCopy.map(function(arg) {
            return macro $i{arg} = $i{arg}.Copy();
        });

        switch (func.expr.expr) {
            case EBlock(exprs): {
                for (e in initExprs) {
                    exprs.unshift(e);
                }
            }
            default: {
                func.expr = macro $b{[func.expr].concat(initExprs)};
            }
        }

        return true;
    }

    static function AddAssignCopies(func: Function): Bool {
        var valueIdents = [];
        for (arg in func.args) {
            if (arg.type == null) continue;
            if (MetadataIsRef(arg.meta)) continue;
            if (!IsValueType(arg.type)) continue;
            valueIdents.push(arg.name);
        }
        return AddAssignCopiesRecurse(func.expr.expr, valueIdents);
    }

    static function AddAssignCopiesRecurse(expr: ExprDef, valueIdents: Array<String>): Bool {
        var changesMade = false;

        switch (expr) {
            case EBlock(children): {
                for (exp in children) {
                    var result = AddAssignCopiesRecurse(exp.expr, valueIdents);
                    if (!changesMade) changesMade = result;
                }
            }
            case EBinop(op, first, second): {
                switch (op) {
                    case OpAssign: {
                        // trace("ASSIGNMENT: " + ExprTools.toString(second));

                        switch (second.expr) {
                            case EConst(c): {
                                switch (c) {
                                    case CIdent(ident) if (valueIdents.contains(ident)): {
                                        second.expr = (macro $i{ident}.Copy()).expr;
                                        changesMade = true;
                                    }
                                    default:
                                }
                            }
                            default:
                        }
                    }
                    default: // ignore
                }
            }
            case EVars(vars): {
                for (child in vars) {
                    // trace("VARIABLE: " + ExprTools.toString(child.expr));

                    // trace("VARIABLE: " + printer.printExpr(child.expr) + " TYPE: " + child.expr?.expr);
                    // trace("VARIABLE: " + ExprTools.toString(child.expr) + " POS: " + child.namePos);

                    switch (child.expr?.expr) {
                        case ENew(t, params): {
                            var complexType = ComplexType.TPath(t);
                            if (IsValueType(complexType)) {
                                valueIdents.push(child.name);
                                trace(child.name + " added to idents");
                            }
                        }
                        case EConst(c): {
                            switch (c) {
                                case CIdent(ident) if (valueIdents.contains(ident)): {
                                    // convert into function call
                                    child.expr = macro $i{ident}.Copy();
                                    changesMade = true;
                                }
                                default: // nothing
                            }
                        }
                        default: // still nothign
                    }
                }
            }
            default: {
                // do nothing yet
            }
        }
        return changesMade;
    }

    // METADATA UTILS
    static function MetadataIsRef(metadata: Metadata): Bool {
        for (entry in metadata) {
            if (entry.name == REF_META) return true;
        }
        return false;
    }

    static function MetadataHasAnyIgnored(metadata: Metadata): Bool {
        for (entry in metadata) {
            if (IGNORE_META.contains(entry.name)) return true;
        }
        return false;
    }

    static function AccessorHasAnyIgnored(accessor: MetaAccess): Bool {
        for (meta in IGNORE_META) {
            if (accessor.has(meta)) return true;
        }
        return false;
    }

    // TYPE UTILS
    static function IsValueType(type: ComplexType): Bool {
        switch (type) {
            case TPath(path): {
                try {
                    var firstType = ComplexTypeTools.toType(type);
                    var currentType = firstType;

                    while (true) {
                        switch (currentType) {
                            case TInst(t, _): {
                                if (t.get().meta.has(VALUE_META)) {
                                    return true;
                                }
                                return false;
                            }
                            case TAbstract(t, _): {
                                if (t.get().meta.has(VALUE_META)) {
                                    return true;
                                } else if (t.get().meta.has(":coreType")) {
                                    return false;
                                } else {
                                    currentType = t.get().type;
                                }
                            }
                            default: {
                                break;
                            }
                        }
                    }
                } catch (e) {
                    // Failed to find type
                }
            }
            default: // wtf are you
        }
        return false;
    }

    static function ListValueTypes(arr: Array<ModuleType>) {
        var allValueTypes = [];

        for (type in arr) {
            var initialType = TypeTools.fromModuleType(type);
            var currentType = initialType;

            var loop = true;

            while (loop) {
                switch (currentType) {
                    case TInst(cls, _): {
                        if (cls.get().meta.has(VALUE_META)) {
                            allValueTypes.push(initialType);
                        }
                        loop = false;
                    }
                    case TAbstract(abs, _): {
                        if (abs.get().meta.has(VALUE_META)) {
                            allValueTypes.push(initialType);
                            loop = false;
                        } else if (abs.get().meta.has(":coreType")) {
                            loop = false; // Core types don't have an underlying type. Break out or we will be stuck.
                        } else {
                            currentType = abs.get().type;
                        }
                    }
                    default: {
                        loop = false; // Ignore others
                    }
                }
            }
        }

        trace("All value types:");
            for (type in allValueTypes) {
                switch (type) {
                    case TInst(t, _): {
                        trace(t.toString());
                    }
                    case TAbstract(t, _): {
                        trace(t.toString());
                    }
                    default:
                }
            }
    }

}

#end
