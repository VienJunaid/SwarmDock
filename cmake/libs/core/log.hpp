#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <string_view>

namespace swarmdock::core {
    enum class LogLevel { Debug, Info, Warn, Error };

    inline const char* to_string(LogLevel lvl) {
        switch (lvl) {
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Info: return "INFO";
            case LogLevel::Warn: return "WARN";
            case LogLevel::Error: return "ERROR";
        }
        return "INFO";
    }

    class Logger {
        public:
            static Logger& instance() {
                static Logger L;
                return L;
            }

            void set_level(LogLevel lvl) { level_ = lvl; }

            void log(LogLevel lvl, std::string_view msg) {
                if (static_cast<int>(lvl) < static_cast<int>(level_)) return;
                std::lock_guard<std::mutex> lock(mu_);
                std::cerr << "[" << to_string(lvl) << "]" << msg << "\n";
            }

            private:
                Logger() = default;
                std::mutex mu_;
                LogLevel level_{LogLevel::Info};
    };

    inline void log_debug(std::string_view msg) { Logger::instance().log(LogLevel::Debug, msg); }
    inline void log_info(std::string_view msg) { Logger::instance().log(LogLevel::Info, msg); }
    inline void log_warn(std::string_view msg) { Logger::instance().log(LogLevel::Warn, msg); }
    inline void log_error(std::string_view msg) { Logger::instance().log(LogLevel::Error, msg); }
} //namespace swarmdock::core



