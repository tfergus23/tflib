#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>

namespace tflib{
    enum class log_level {OFF = 0,FATAL = 1,ERROR = 2,WARN = 3,INFO = 4,DEBUG = 5,TRACE = 6};


    class std_out_appender{
    public:
        log_level max_level;
        log_level min_level;
        std_out_appender(log_level level, log_level min_level=log_level::OFF);
        void log(const std::string& message, log_level log_level);
    };

    class std_err_appender{
    public:
        log_level max_level;
        log_level min_level;
        std_err_appender(log_level level, log_level min_level=log_level::OFF);
        void log(const std::string& message, log_level log_level);
    };

    class file_appender{
    public:
        log_level max_level;
        log_level min_level;
        file_appender(const file_appender& that);
        file_appender(log_level level, const std::string& file_path, log_level min_level=log_level::OFF);
        void log(const std::string& message, log_level log_level);

    private:
        const std::string m_file_path;
        std::ofstream m_ofstream;
    };

    class logger{
    public:
        void set_prefix(std::function<std::string(const std::string&)> prefix);

        void set_suffix(std::function<std::string(const std::string&)> suffix);

        void fatal(const std::string& message);
        void error(const std::string& message);
        void warn(const std::string& message);
        void info(const std::string& message);
        void debug(const std::string& message);
        void trace(const std::string& message);

        void add_std_out_appender(const std_out_appender& appender);
        void add_std_err_appender(const std_err_appender& appender);
        void add_file_appender(const file_appender& appender);

        static std::string level_to_string(log_level level);
    private:
        void log(const std::string& message, log_level level);
        std::function<std::string(const std::string&)> m_prefix = [](const std::string&){return "";};
        std::function<std::string(const std::string&)> m_suffix = [](const std::string&){return "";};
        std::vector<std_out_appender> m_std_out_appenders;
        std::vector<std_err_appender> m_std_err_appenders;
        std::vector<file_appender> m_file_appenders;
    };
}