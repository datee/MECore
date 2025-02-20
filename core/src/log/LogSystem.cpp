//
// Created by ryen on 12/22/24.
//

#include <spdlog/spdlog.h>
#include <spdlog/sinks/ostream_sink.h>

#include "MECore/log/LogSystem.h"

namespace ME::log {
    // TODO: i think using a stringstream here eventually causes a crash, dont....
    bool Initialize() {
        stream = std::stringstream();
        auto sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(stream);
        spdlog::default_logger()->sinks().push_back(sink);

        return true;
    }
}
