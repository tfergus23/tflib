#pragma once
#include <iostream>
#include <string>

namespace tflib{
    enum class log_level {OFF = 0,FATAL = 1,ERROR = 2,WARN = 3,INFO = 4,DEBUG = 5,TRACE = 6};

    class logger{
    public:
        std::string get_prefix();
        void set_prefix(const std::string& prefix);

        std::string get_suffix();
        void set_suffix(const std::string& suffix);

        void fatal(const std::string& message);
        void error(const std::string& message);
        void warn(const std::string& message);
        void info(const std::string& message);
        void debug(const std::string& message);
        void trace(const std::string& message);

        log_level level = log_level::FATAL;
    private:
        void log(const std::string& message);
        std::string m_prefix = "";
        std::string m_suffix = "";
    };
}