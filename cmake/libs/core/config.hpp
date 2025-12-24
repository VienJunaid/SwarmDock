#pragma once

#include <cstdint>


namespace swarmdock::core {
    struct CoreConfig {
        std::int64_t heartbeat_period_ms = 250;
        std::int64_t heartbeat_timeout_ms = 1500;

        std::int64_t telemetry_period_ms = 200;
        std::int64_t assignment_lease_ms = 2000;
    
    };

} //namespace swarmdock::core 