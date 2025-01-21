package me.game;

import me.internal.EngineObject;
import me.game.GameTransform;

final class GameObject extends EngineObject {
    public var Scene(default, never): Scene;

    public var Parent(default, never): GameObject;
    public var Transform(default, never): GameTransform;
    public var Components(default, never): ComponentManager;
}
