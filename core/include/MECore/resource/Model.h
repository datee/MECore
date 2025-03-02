//
// Created by ryen on 2/19/25.
//

#pragma once

#include <memory>
#include <nvrhi/nvrhi.h>

#include "Mesh.h"
#include "Material.h"

namespace ME::resource {
    // A model can have multiple meshes, default materials, and a skeleton.
    class Model {
        public:
        std::vector<std::shared_ptr<Mesh>> meshes;
        // For now, materials should match the size of meshes. This will be changed later.
        std::vector<std::shared_ptr<Material>> materials;

        Model() = default;

        void TryAddUpload(nvrhi::ICommandList* commandList) const;
    };
}
