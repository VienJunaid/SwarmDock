#pragma once

#include <cstdint>
#include <functional>
#include <ostream>


namespace sd {
    // Each ID has its own type to prevent mixing
    // zero means unset 
    struct RobotId {
        std::uint32_t value = 0;
    };

    struct TaskId {
        std::uint32_t value = 0;
    };

    struct MapNodeId {
        std::uint32_t value = 0;
    };

    // Comparisons (for maps and test, etc)
    // This allows you to confirm and answer questions like: Is this task already assigned to this robot?
    // Makes super easy debugging 
    inline bool operator==(RobotId a, RobotId b) {
        return a.value == b.value;

    }

    inline bool operator==(TaskId a, TaskId b) {
        return a.value == b.value;
    }

    inline bool operator==(MapNodeId a, MapNodeId b) {
        return a.value == b.value;
    }
}