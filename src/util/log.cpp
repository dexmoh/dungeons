#include "util/log.hpp"

#include "pch.hpp"

void Log::write(const std::string& msg, Log::Level level, bool new_line) {
    if (msg.empty())
        return;

    std::string output = std::format(
        "[{:%T}]", 
        std::chrono::floor<std::chrono::seconds>(
            std::chrono::system_clock::now()
        )
    );

    switch (level) {
        case Log::Level::INFO:
            output += "[INFO] ";
            break;
        case Log::Level::WARNING:
            output += "[WARNING] ";
            break;
        case Log::Level::ERROR:
            output += "[ERROR] ";
            break;
        case Log::Level::FATAL:
            output += "[FATAL] ";
            break;
    }

    output += msg;
    if (new_line)
        output += '\n';

    std::cout << output;
}
