#pragma once
#include <iostream>
#include <string>

namespace tflib{
    enum logLevel {OUT,ERROR,DEBUG};
    static logLevel mLogLevel;

    void setLogLevel(const std::string &level);
    void logOut(const std::string &message);
    void logError(const std::string &message);
    void logDebug(const std::string &message);
    void logFatal(const std::string &message, int errCode=1);
}