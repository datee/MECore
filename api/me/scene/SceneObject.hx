package me.scene;

import me.internal.EngineObject;

abstract class SceneObject extends EngineObject {
    public var Enabled(get, set): Bool;

    public var Scene(default, never): Scene;    
    public var Transform(default, never): SceneTransform;

    inline function get_Enabled(): Bool {
        return true;
    }

    inline function set_Enabled(value: Bool): Bool {
        return true;
    }
}
