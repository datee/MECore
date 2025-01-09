package me.game;

import me.internal.EngineObject;
import me.game.GameTransform;

final class GameObject extends EngineObject {
    public var Scene(default, null): Scene;

    public var Parent(default, null): GameObject;
    public var Transform(default, null): GameTransform;
    public var Components(default, null): ComponentManager;
}
