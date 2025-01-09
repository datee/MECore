package me.game;

import me.internal.Pointer;
import me.game.Component;
import me.internal.game.GameObjectModule;
import me.Log;

final class ComponentManager extends GameObjectModule {
    var list: Array<Component>;
    var firstUpdates: Map<Component, Bool>;

    /**
        Creates a new component of `T`
    **/
    public function Create<T: Component>(t: Class<T>): T {
        var hlClass = cast(t, hl.BaseType.Class);
        var comp = hlClass.__type__.allocObject();
        SetupComponent(cast comp);
        return cast comp;
    }

    // ENGINE CALLS
    function ME_StartCheck(): Void {
        for (comp in list) {
            if (!comp.Enabled) continue;
            if (!firstUpdates[comp]) {
                comp.OnStart();
                firstUpdates[comp] = true;
            }
        }
    }

    function ME_Update(): Void {
        for (comp in list) {
            if (!comp.Enabled) continue;

            comp.OnUpdate();
        }
    }

    function ME_FixedUpdate(): Void {
        for (comp in list) {
            if (!comp.Enabled) continue;

            comp.OnFixedUpdate();
        }
    }

    function ME_LateUpdate(): Void {
        for (comp in list) {
            if (!comp.Enabled) continue;

            comp.OnLateUpdate();
        }
    }

    function ME_PreRender(): Void {
        for (comp in list) {
            if (!comp.Enabled) continue;

            comp.OnPreRender();
        }
    }

    function ME_CreateComponent(type: hl.Type): Void {
        Log.Info('Recieved type: ${type.getTypeName()}');
        var object = cast(type.allocObject(), Component);
        if (object == null) {
            Log.Error('Type ${type.getTypeName()} failed to cast.');
            return;
        }
        
        SetupComponent(object);

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

    // UTIL
    function SetupComponent(comp: Component): Void {
        comp.ME_Initialize(GameObject);

        list.push(comp);
        firstUpdates[comp] = false;

        comp.OnLoaded();
    }
}
