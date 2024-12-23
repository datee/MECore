//
// Created by ryen on 12/22/24.
//

#include "LogSystem.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/ostream_sink.h"

namespace me::log {
    bool Initialize() {
        stream = std::ostringstream();
        auto sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(stream);
        auto logger = std::make_shared<spdlog::logger>("main", sink);

        spdlog::set_default_logger(logger);

        return true;
    }
}
