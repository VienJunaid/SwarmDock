#pragma once

#include <cstdint>
#include "core/ids.hpp"
#include "core/geometry.hpp"

namespace sd {
    // using uint8_t to ensure compiler use 8-bit unsinged integer type across different systems and compilers

    enum class RobotMode: std::uint8_t {
        Idle = 0,
        Busy = 1,
        Error = 2
    };

    // Snapshot of a robot at its current moment in time
    struct RobotState {
        // defualt constructor
        RobotId id{};
        Vec2 position{};
        RobotMode mode = RobotMode::Idle; // default state 
    };



}