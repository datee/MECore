package me.game;

import me.game.ComponentManager;
import me.game.GameTransform;
import me.game.GameObject;

abstract class Component {
    // var GameObject(get, never): GameObject;
    // var Transform(get, never): GameTransform;
    // var Components(get, never): ComponentManager;

    // ENGINE CALLBACKS

    /**
        Called when the object is loaded.
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
}
