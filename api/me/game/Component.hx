package me.game;

import me.internal.UUID;
import me.IValid;
import me.game.ComponentManager;
import me.game.GameTransform;
import me.game.GameObject;

using me.IValid.IValidExt;

/**
    A scripted component on a game object.
**/

@:allow(me.game)
abstract class Component implements IValid {
    public var Enabled(default, default): Bool;

    public var GameObject(default, null): GameObject;
    public var UUID(default, null): UUID;

    public var Transform(get, never): GameTransform;
    public var Components(get, never): ComponentManager;
    public var Scene(get, never): Scene;

    @:inheritDoc
    public var IsValid(get, never): Bool;

    final inline function get_IsValid(): Bool {
        return GameObject.IsValidSafe();
    }

    final inline function get_Transform(): GameTransform {
        return GameObject.Transform;
    }

    final inline function get_Components(): ComponentManager {
        return GameObject.Components;
    }

    final inline function get_Scene(): Scene {
        return GameObject.Scene;
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

    function OnEnable(): Void {

    }

    function OnDisable(): Void {
        
    }

    function OnDestroy(): Void {
        
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

    function OnPreRender(): Void {
        
    }

    public final function hashCode(): Int {
        return 0;
    }
}
