package me.game;

import me.IValid;
import me.game.ComponentManager;
import me.game.GameTransform;
import me.game.GameObject;

using me.IValid.IValidExt;

/**
    A scripted component on a game object.
**/

abstract class Component implements IValid {
    public var Enabled(default, default): Bool;

    public var GameObject(default, null): GameObject;
    public var Transform(default, null): GameTransform;
    public var Components(default, null): ComponentManager;

    public var IsValid(get, never): Bool;

    // Hide constructor
    private final function new() {

    }

    final inline function get_IsValid(): Bool {
        return GameObject.IsValidSafe();
    }

    // ENGINE CALLBACKS

    /**
        Called when the component is loaded/created.
    **/
    function OnLoaded(): Void {

    }

    /**
        Called before the first update.
    **/
    function OnStart(): Void {

    }

    /**
        Called every frame. (If enabled of course.)
    **/
    function OnUpdate(): Void {
        
    }

    /**
        Called after engine systems update. (Before rendering.)
    **/
    function OnLateUpdate(): Void {

    }

    /**
        Called before the physics world is simulated.
    **/
    function OnFixedUpdate(): Void {

    }

    // INTERNAL FUNCTIONS
    public final function ME_Initialize(manager: ComponentManager): Void {
        Components = manager;
        GameObject = manager.GameObject;
        Transform = manager.GameObject.Transform;
        Enabled = true;
    }
}
