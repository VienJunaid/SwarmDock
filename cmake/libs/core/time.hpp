#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace swarmdock::core {
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
    using Duration = Clock::duration;

    /*
        inline - tells the compiler and linker that a function
        may be defined in multiple files, and may be expanded directly
        at the call site instead of being called like a normal function.

        rule of thumb: if a function definition is in a header,
        and will be included in multiple .cpp files, make it inline
    */
    inline TimePoint now() { return Clock::now(); }

    inline std::int64_t to_ms(Duration d) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
    }

    inline Duration ms(std::int64_t v) {
        return std::chrono::milliseconds(v);
    }

} // namespace swarmdock::core