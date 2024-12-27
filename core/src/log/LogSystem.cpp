//
// Created by ryen on 12/22/24.
//

#include "LogSystem.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/ostream_sink.h"

namespace me::log {
    bool Initialize() {
        stream = std::stringstream();
        auto sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(stream);
        spdlog::default_logger()->sinks().push_back(sink);

        return true;
    }
}
