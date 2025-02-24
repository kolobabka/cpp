#pragma once

#include <iostream>
#include <source_location>
#include <string_view>

namespace logger {

void log(std::string_view Msg, const std::source_location &Loc = 
            std::source_location::current()) {
    std::clog << "[" << Loc.file_name () << ":" << Loc.line () << "] "
              << Loc.function_name () << "(): " << Msg << std::endl;
}

class Logger final {
    std::source_location Loc;
public:
    Logger(const std::source_location& Loc = 
            std::source_location::current()) : Loc (Loc) {
        log("Start Message...", Loc);
    }
    
    // We definitely doesn't want to have copy/move semantic for Logger :) 
    Logger(const Logger &) = delete;
    Logger(Logger &&) = delete;

    Logger &operator=(const Logger &) = delete;
    Logger &operator=(Logger &&) = delete;

    ~Logger() {
        log("Final Message...", Loc);
    }
};
} // namespace logger