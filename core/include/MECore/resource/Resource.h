//
// Created by ryen on 2/28/25.
//

#pragma once

namespace ME::resource {
    class Resource {
        public:
        virtual ~Resource() = default;

        virtual bool IsValid() const { return true; }
        virtual void Clone() const { }
    };
}
