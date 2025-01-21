package me.game;

import me.internal.Pointer;
import me.game.Component;
import me.internal.game.GameObjectModule;
import me.Log;

final class ComponentManager extends GameObjectModule {
    var components: Array<Component>;
    var startRan: Array<Bool>;
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
        for (i in new IntIterator(0, components.length)) {
            var comp = components[i];

            if (!comp.Enabled) continue;
            if (startRan[i]) continue;

            comp.OnStart();
            startRan[i] = true;
        }
    }

    function ME_Update(): Void {
        for (comp in components) {
            if (!comp.Enabled) continue;

            comp.OnUpdate();
        }
    }

    function ME_FixedUpdate(): Void {
        for (comp in components) {
            if (!comp.Enabled) continue;

            comp.OnFixedUpdate();
        }
    }

    function ME_LateUpdate(): Void {
        for (comp in components) {
            if (!comp.Enabled) continue;

            comp.OnLateUpdate();
        }
    }

    function ME_PreRender(): Void {
        for (comp in components) {
            if (!comp.Enabled) continue;

            comp.OnPreRender();
        }
    }

    function ME_CreateComponent(type: hl.Type): Void {
        Log.Info('ME_CreateComponent: Recieved ${type.getTypeName()}');
        var object = cast(type.allocObject(), Component);
        if (object == null) {
            Log.Error('ME_CreateComponent: Type ${type.getTypeName()} failed to cast.');
            return;
        }
        
        SetupComponent(object);

        Log.Info('ME_CreateComponent: Created ${type.getTypeName()}');
    }

    override function ME_Initialize(ptr: Pointer) {
        super.ME_Initialize(ptr);
        components = new Array<Component>();
        startRan = new Array<Bool>();
    }

    override function ME_Destroy() {
        components = null;
        startRan = null;
        super.ME_Destroy();
    }

    // UTIL
    function SetupComponent(comp: Component): Void {
        comp.Enabled = true;
        comp.GameObject = GameObject;

        components.push(comp);
        startRan.push(false);

        comp.OnLoaded();
    }
}
