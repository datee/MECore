package me.game;

import haxe.Constraints.Constructible;
import me.game.Component;
import me.internal.game.GameObjectModule;

final class ComponentManager extends GameObjectModule {
    var list: Array<Component>;

    @:generic
    function Create<T: Component & Constructible<Void->Void>>(): T {
        var comp = new T();
        list.push(comp);
        return comp;
    }

    function ME_CreateComponent(type: hl.Type): Component {
        return null;
    }

    override function ME_Destroy() {
        list = null; // release references
        super.ME_Destroy();
    }
}
