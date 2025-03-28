//
// Created by ryen on 2/28/25.
//

#include "MECore/resource/Model.h"

namespace ME::resource {
    void Model::UpdateBuffers() {
        for (const auto mesh : meshes) {
            if (!mesh->IsDirty()) continue;
            mesh->UpdateBuffers();
        }
    }

    void Model::UploadBuffers(nvrhi::ICommandList* cmd) {
        for (const auto mesh : meshes) {
            mesh->UploadBuffers(cmd);
        }
    }
}
