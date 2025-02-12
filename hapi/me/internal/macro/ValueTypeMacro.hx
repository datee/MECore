package me.internal.macro;

import haxe.macro.Expr.Metadata;
#if macro

import haxe.macro.Type;
import haxe.macro.TypeTools;
import haxe.macro.Context;
import haxe.macro.Compiler;
import haxe.macro.ComplexTypeTools;
import haxe.macro.Expr.ComplexType;
import haxe.macro.Expr.Function;

// Made with help from SomeRanDev and PXshadow.
// seriously i wouldve stopped using this language if it werent for you guys.

class ValueTypeMacro {
    static final VALUE_META: String = ":valueType";
    static final REF_META: String = ":ref";
    static final IGNORE_META: Array<String> = [":hlNative"];

    static var allValueTypes: Array<Type>;
    static var verboseActive: Bool;

    public static function Init(?verbose: Bool = false) {
        allValueTypes = [];
        verboseActive = verbose;

        // on after typing happens after these build metadatas
        // however value types are cached during on after typing
        // wrong order.
        Context.onAfterTyping(ResolveValueTypes);
		Compiler.addGlobalMetadata("", "@:build(me.internal.macro.ValueTypeMacro.BuildProcess())");
	}

    public static function ResolveValueTypes(arr: Array<ModuleType>) {
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

        if (verboseActive) {
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

    public static function BuildProcess() {
        final localClass = Context.getLocalClass();
        if (localClass != null) {
            if (AccessorHasAnyIgnored(localClass.get().meta)) {
                if (verboseActive) {
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
                    // AddArgCopies(func);
                }
                default:
            }
        }

        return fields;
    }

    public static function AddArgCopies(func: Function): Bool {
        final argsToCopy = [];

        // Resolve args to copy
        for (arg in func.args) {
            if (!IsValueType(arg.type)) continue;
            argsToCopy.push(arg.name);
        }

        if (argsToCopy.length <= 0) return false;

        final initExprs = argsToCopy.map(function(arg) {
            return macro var $arg = $i{arg}.Copy();
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

	public static function applyCopy() {
		final fields = Context.getBuildFields();

		var changed = false;

        // trace(macro : me.math.Vector3);

		for(f in fields) {
			switch(f.kind) {
				case FFun(func) if(func.expr != null): {
					// Find all arguments that need `.copy()`.
					final copyNames = [];
					for(a in func.args) {
                        if (a.type == null) continue;

                        var isValue = false;

                        switch (a.type) {
                            case ComplexType.TPath(path): {
                                try {
                                    var firstType = ComplexTypeTools.toType(a.type ?? null);

                                    var loop = true;
                                    var currentType = firstType;

                                    while (loop) {
                                        switch (currentType) {
                                            case TInst(t, _): {
                                                if (t.get().meta.has(":valueType")) {
                                                    trace('${t.get().name} is a value type!');
                                                    isValue = true;
                                                }
                                                loop = false;
                                            }
                                            case TAbstract(t, _): {
                                                if (t.get().meta.has(":valueType")) {
                                                    trace('${t.get().name} is a value type!');
                                                    isValue = true;
                                                    loop = false;
                                                } else if (t.get().meta.has(":coreType")) {
                                                    loop = false;
                                                } else {
                                                    currentType = t.get().type;
                                                }
                                            }
                                            case _: {
                                                loop = false;
                                            }
                                        }
                                    }
                                } catch (e) {
                                    // failed lol
                                }
                            }
                            case _:
                        }

						switch(a.type) {
							// Find types...
							// case macro : Vec: {
							// 	copyNames.push(a.name);
							// }
							case _:
						}
					}

					if(copyNames.length == 0) {
						continue;
					}

					// Convert list of argument names to `copy` expressions.
					final copyExpressions = copyNames.map(function(name) {
						// $i{SOMETHING} => Converts String variable SOMETHING to identifier.
						// Works automatically as $SOMETHING after `var`.
						return macro var $name = $i{name}.copy();
					});

					// Use copy of original function expression so it isn't recursive.
					final copyOfOriginal = Reflect.copy(func.expr);

					// Create new expression using original expression + copy expressions.
					final newFunctionExpr = macro {
						@:mergeBlock $b{copyExpressions};
						$copyOfOriginal;
					}

					// Assign new expression to function object.
					func.expr = newFunctionExpr;

					changed = true;
				}
				case _:
			}
		}

		return changed ? fields : null;
	}

    public static function MetadataHasAnyIgnored(metadata: Metadata): Bool {
        for (entry in metadata) {
            if (IGNORE_META.contains(entry.name)) return true;
        }
        return false;
    }

    public static function AccessorHasAnyIgnored(accessor: MetaAccess): Bool {
        for (meta in IGNORE_META) {
            if (accessor.has(meta)) return true;
        }
        return false;
    }

    public static function IsValueType(type: ComplexType): Bool {
        return allValueTypes.contains(ComplexTypeTools.toType(type));
    }

    public static function IsValueTypePure(type: ComplexType): Bool {
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
                                } else if (t.get().meta.has(VALUE_META)) {
                                    return false;
                                } else {
                                    currentType = t.get().type;
                                }
                            }
                            case _: {
                                break;
                            }
                        }
                    }
                } catch (e) {
                    // Failed to find type
                }
            }
            case _: // wtf are you
        }
        return false;
    }
}

#end