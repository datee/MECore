//
// Created by ryen on 2/20/25.
//

#pragma once

#include <vector>

#include "MECore/math/Types.h"

namespace ME::node {
    // A single mesh.
    class Mesh {
        protected:
        std::vector<PackedVector3> vertexBuffer;
    };
}
