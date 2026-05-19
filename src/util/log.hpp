#pragma once

#include <string>

class Log {
public:
    enum class Level {
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
