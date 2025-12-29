#pragma once

#include <cstdint>
#include "cmake/libs/core/ids.hpp"
#include "cmake/libs/core/geometry.hpp"

namespace sd {
    // Mission
    enum class MissionStatus : std::uint8_t {
        Queued = 0,
        Active = 1,
        Done = 2,
        Failed = 3
    };

    struct Mission {
        std::uint32_t id = 0;
        std::vector<TaskId> tasks; // vector is a dynamic array 
        MissionStatus status = MissionStatus::Queued;
    };
}