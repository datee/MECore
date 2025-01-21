//
// Created by ryen on 1/1/25.
//

#include "Transform.h"

namespace me::math {
    Vector3 Transform::EnterPoint(const Vector3& worldPoint) const {
        return (rotation.Inversed() * (worldPoint - position)) / scale;
    }

    Vector3 Transform::EnterDirection(const Vector3& worldDir) const {
        return (rotation.Inversed() * worldDir) / scale;
    }

    Vector3 Transform::EnterVector(const Vector3& worldVector) const {
        return worldVector / scale;
    }

    Quaternion Transform::EnterQuaternion(const Quaternion& worldRot) const {
        return rotation.Inversed() * worldRot;
    }

    Transform Transform::Enter(const Transform& world) const {
        return { EnterPoint(world.position), EnterQuaternion(world.rotation), EnterVector(world.scale) };
    }

    Vector3 Transform::ExitPoint(const Vector3& localPoint) const {
        return position + (rotation * (localPoint * scale));
    }

    Vector3 Transform::ExitDirection(const Vector3& localDir) const {
        return rotation * (localDir * scale);
    }

    Vector3 Transform::ExitVector(const Vector3& localVector) const {
        return localVector / scale;
    }

    Quaternion Transform::ExitQuaternion(const Quaternion& localRot) const {
        return localRot * rotation;
    }

    Transform Transform::Exit(const Transform& local) const {
        return { ExitPoint(local.position), ExitQuaternion(local.rotation), ExitVector(local.scale) };
    }

    Matrix4x4 Transform::ToTRS() const {
        return Matrix4x4::sRotationTranslation(rotation, position).PreScaled(scale);
    }
}
