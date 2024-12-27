package me;

import me.GameObject;

abstract class GameObjectModule {
    public var GameObject(default, null): GameObject;

    function new(obj: GameObject) {
        GameObject = obj;
    }
}
