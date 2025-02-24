//
// Created by ryen on 2/24/25.
//

#include "MECore/node/game/GameTransform.h"
#include "MECore/node/game/GameNode.h"

namespace ME::node {
    inline void Util_LocalToWorld(GameNode* parent, const Transform& local, Transform& world) {
        if (parent == nullptr) {
            world = local;
        } else {
            const auto& transform = parent->GetTransform().Raw();
            world = transform.Exit(local);
        }
    }

    inline void Util_WorldToLocal(GameNode* parent, Transform& local, const Transform& world) {
        if (parent == nullptr) {
            local.position = world.position;
            local.rotation = world.rotation;
        } else {
            const auto& transform = parent->GetTransform().Raw();
            local.position = transform.EnterPoint(world.position);
            local.rotation = transform.EnterQuaternion(world.rotation);
        }
    }

    void GameTransform::SetPosition(const Vector3& pos) {
        world.position = pos;
        Util_WorldToLocal(gameNode->GetGameParent(), local, world);
    }

    void GameTransform::SetRotation(const Quaternion& rot) {
        world.rotation = rot;
        Util_WorldToLocal(gameNode->GetGameParent(), local, world);
    }

    void GameTransform::SetLocalPosition(const Vector3& pos) {
        local.position = pos;
        Util_LocalToWorld(gameNode->GetGameParent(), local, world);
    }

    void GameTransform::SetLocalRotation(const Quaternion& rot) {
        local.rotation = rot;
        Util_LocalToWorld(gameNode->GetGameParent(), local, world);
    }

    void GameTransform::SetLocalScale(const Vector3& scale) {
        local.scale = scale;
        Util_LocalToWorld(gameNode->GetGameParent(), local, world);
    }
}
