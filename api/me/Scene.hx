package me;

import me.physics.PhysicsWorld;
import me.game.GameWorld;
import me.scene.SceneWorld;
import me.internal.EngineObject;

final class Scene extends EngineObject {
    public var GameWorld(default, never): GameWorld;
    public var PhysicsWorld(default, never): PhysicsWorld;
    public var SceneWorld(default, never): SceneWorld;
}
