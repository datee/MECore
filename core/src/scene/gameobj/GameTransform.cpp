//
// Created by ryen on 1/1/25.
//

#include "GameTransform.h"
#include "GameObject.h"

namespace me::scene {
    inline void Util_LocalToGlobal(GameObject* parent, const math::Transform& local, math::Transform& global) {
        if (parent == nullptr) {
            global = local;
        } else {
            const auto& transform = parent->GetTransform().GlobalRaw();
            global = transform.Exit(local);
        }
    }

    inline void Util_GlobalToLocal(GameObject* parent, math::Transform& local, const math::Transform& global) {
        if (parent == nullptr) {
            local.position = global.position;
            local.rotation = global.rotation;
        } else {
            const auto& transform = parent->GetTransform().GlobalRaw();
            local.position = transform.EnterPoint(global.position);
            local.rotation = transform.EnterQuaternion(global.rotation);
        }
    }

    GameTransform::GameTransform(GameObject* obj) : GameObjectModule(obj, u"me.game.GameTransform") {
        world = math::Transform::identity;
        local = math::Transform::identity;
        eulerAngles = math::Vector3(0, 0, 0);
    }

    inline void GameTransform::SetGlobalPosition(const math::Vector3& pos) {
        world.position = pos;
        Util_GlobalToLocal(gameObject->GetParent(), local, world);
    }

    inline void GameTransform::SetGlobalRotation(const math::Quaternion& rot) {
        world.rotation = rot;
        Util_GlobalToLocal(gameObject->GetParent(), local, world);
    }

    inline void GameTransform::SetLocalPosition(const math::Vector3& pos) {
        local.position = pos;
        Util_LocalToGlobal(gameObject->GetParent(), local, world);
    }

    inline void GameTransform::SetLocalRotation(const math::Quaternion& rot) {
        local.rotation = rot;
        Util_LocalToGlobal(gameObject->GetParent(), local, world);
    }

    inline void GameTransform::SetLocalScale(const math::Vector3& scale) {
        local.scale = scale;
        Util_LocalToGlobal(gameObject->GetParent(), local, world);
    }
}
