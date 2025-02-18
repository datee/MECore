package me.components;

import me.asset.MeshAsset;
import me.scene.SceneMesh;
import me.game.Component;
import me.Log;

final class MeshRenderer extends Component {
    public var Mesh(get, set): MeshAsset;

    public var MeshRef(default, null): SceneMesh;

    inline function get_Mesh(): MeshAsset {
        return MeshRef.Mesh;
    }

    inline function set_Mesh(value: MeshAsset): MeshAsset {
        return MeshRef.Mesh = value;
    }

    override function OnLoaded(): Void {
        MeshRef = SceneMesh.Create();
        Scene.SceneWorld.AddObject(MeshRef);

        Log.Info("MeshRenderer created");
    }

    override function OnPreRender(): Void {
        MeshRef.Transform.Raw = Transform.World;
    }
}
