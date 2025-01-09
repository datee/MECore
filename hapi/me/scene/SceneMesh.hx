package me.scene;

import me.internal.Pointer;
import me.asset.MeshAsset;

final class SceneMesh extends SceneObject {
    public var Mesh(get, set): MeshAsset;

    inline function get_Mesh(): MeshAsset {
        return cast SceneMeshBindings.scene_sceneobj_mesh_get_mesh(pointer);
    }

    inline function set_Mesh(value: MeshAsset): MeshAsset {
        SceneMeshBindings.scene_sceneobj_mesh_set_mesh(pointer, value.pointer);
        return value;
    }

    public static function Create(): SceneMesh {
        return cast SceneMeshBindings.scene_sceneobj_mesh_create();
    }
}

@:allow(me.scene.SceneMesh)
@:hlNative("MECore")
private extern class SceneMeshBindings {
    private static function scene_sceneobj_mesh_create(): Dynamic;
    private static function scene_sceneobj_mesh_get_mesh(ptr: Pointer): Dynamic;
    private static function scene_sceneobj_mesh_set_mesh(ptr: Pointer, v: Pointer): Void;
}
