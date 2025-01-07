package me.game;

import me.internal.Pointer;
import me.game.Component;
import me.internal.game.GameObjectModule;
import me.Log;

final class ComponentManager extends GameObjectModule {
    var list: Array<Component>;
    var firstUpdates: Map<Component, Bool>;

    @:generic
    function Create<T: Component>(): T {
        return null;
    }

    function ME_Update(): Void {
        for (comp in list) {
            if (!comp.Enabled) continue;

            if (!firstUpdates[comp]) {
                @:privateAccess
                comp.OnStart();
                firstUpdates[comp] = true;
            }
            @:privateAccess
            comp.OnUpdate();
        }
    }

    function ME_FixedUpdate(): Void {
        for (comp in list) {
            if (!comp.Enabled) continue;

            @:privateAccess
            comp.OnFixedUpdate();
        }
    }

    function ME_LateUpdate(): Void {
        for (comp in list) {
            if (!comp.Enabled) continue;

            @:privateAccess
            comp.OnLateUpdate();
        }
    }

    function ME_CreateComponent(type: hl.Type): Void {
        Log.Info('Recieved type: ${type.getTypeName()}');
        var object = cast(type.allocObject(), Component);
        if (object == null) {
            Log.Error('Type ${type.getTypeName()} failed to cast.');
            return;
        }
        
        @:privateAccess
        object.ME_Initialize(this);

        list.push(object);
        firstUpdates[object] = false;

        @:privateAccess
        object.OnLoaded();

        Log.Info('Created ${type.getTypeName()}');
    }

    override function ME_Initialize(ptr: Pointer) {
        super.ME_Initialize(ptr);
        list = new Array<Component>();
        firstUpdates = new Map<Component, Bool>();
    }

    override function ME_Destroy() {
        list = null;
        firstUpdates = null;
        super.ME_Destroy();
    }
}
