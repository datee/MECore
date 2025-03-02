//
// Created by ryen on 2/28/25.
//

#pragma once

namespace ME::resource {
    class Resource {
        public:
        virtual ~Resource() = default;

        bool IsValid() const { return true; }
        void Clone() const { }
    };
}
