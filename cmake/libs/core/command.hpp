#pragma once

#include <cstdint>

#include "core/ids.hpp"
#include "geometry.hpp"

namespace sd {
    enum class CommandType : std::uint8_t {
        MoveTo = 0,
        Pick = 1,
        Drop = 2,
        Stop = 3
    };

    struct Command {
        RobotId robot{};
        CommandType type = CommandType::Stop;

        // Used only when type == MoveTo
        Vec2 target{};

        // what tasks belond to this commadn 
        TaskId task{};
    };
}

