package me.game;

import me.internal.EngineObject;
import me.game.GameTransform;

final class GameObject extends EngineObject {
    public var Parent(default, never): GameObject;
    public var Transform(default, never): GameTransform;
}
