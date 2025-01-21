package me.components;

import me.game.Component;

final class Camera extends Component {
    override function OnPreRender(): Void {
        Scene.SceneWorld.Camera.Transform.Raw = Transform.World;
    }
}
