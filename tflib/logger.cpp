#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "../include/logger.h"

namespace tflib{

    void setLogLevel(const std::string &newLevel){
        if (newLevel == "debug") mLogLevel = DEBUG;
        else mLogLevel = ERROR;
    }

    std::string currentTimeStamp(){
        auto start = std::chrono::system_clock::now();
        std::time_t startTime = std::chrono::system_clock::to_time_t(start);
        std::string timeString = std::ctime(&startTime);
        timeString = timeString.substr(0,timeString.length()-1);
        return timeString;
    }

    void logOut(const std::string &message){
        std::cout << currentTimeStamp() + "  [INFO] " + message << std::endl;
    }

    void logError(const std::string &message){
        if (mLogLevel >= ERROR)
            std::cerr << currentTimeStamp() + " [ERROR] " + message << std::endl;
    }

    void logDebug(const std::string &message){
        if (mLogLevel >= DEBUG)
            std::cerr << currentTimeStamp() + " [DEBUG] " + message << std::endl;
    }

    void logFatal(const std::string &message, int errCode){
        std::cerr << currentTimeStamp() + " [FATAL] " + message << std::endl;
        throw 1;
    }
}