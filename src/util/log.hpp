#pragma once

#include <string>
#include <cstdint>

class Log {
public:
    enum class Level : std::uint8_t {
        INFO = 0,
        WARNING,
        ERROR,
        FATAL
    };

    // Log a message.
    static void write(
        const std::string& msg,
        Log::Level level = Log::Level::INFO,
        bool new_line = true
    );

};
