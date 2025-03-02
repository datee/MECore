//
// Created by ryen on 2/28/25.
//

#include "MECore/resource/Model.h"

namespace ME::resource {
    void Model::TryAddUpload(nvrhi::ICommandList* commandList) const {
        for (const auto mesh : meshes) {
            if (!mesh->WantsUpload()) continue;
            mesh->AddUpload(commandList);
        }
    }
}
