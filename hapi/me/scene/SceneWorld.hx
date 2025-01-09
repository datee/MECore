package me.scene;

import me.internal.EngineObject;
import me.internal.Pointer;

class SceneWorld extends EngineObject {
    public function AddObject(obj: SceneObject): Void {
        SceneWorldBindings.scene_sceneobj_world_assign(pointer, obj.pointer);
    }
}

@:noDoc
@:allow(me.scene.SceneWorld)
@:hlNative("MECore")
private extern class SceneWorldBindings {
    private static function scene_sceneobj_world_assign(ptr: Pointer, obj: Pointer): Void;
}
