#include "../include/logger.h"
using namespace tflib;

static const std::unordered_map<log_level, std::string> LEVEL_STRINGS = {
    {log_level::OFF, " OFF "},
    {log_level::FATAL, "FATAL"},
    {log_level::ERROR, "ERROR"},
    {log_level::WARN, " WARN"},
    {log_level::INFO, " INFO"},
    {log_level::DEBUG, "DEBUG"},
    {log_level::TRACE, "TRACE"},
};

std_out_appender::std_out_appender(log_level level, log_level min_level) : max_level{level}, min_level{min_level} {}
void std_out_appender::log(const std::string& message, log_level log_level){
    if (log_level <= max_level && log_level >= min_level){
        std::cout << message << '\n';
    }
}

std_err_appender::std_err_appender(log_level level, log_level min_level) : max_level{level}, min_level{min_level} {}
void std_err_appender::log(const std::string& message, log_level log_level){
    if (log_level <= max_level && log_level >= min_level){
        std::cerr << message << '\n';
    }
}

file_appender::file_appender(const file_appender& that) : m_file_path{that.m_file_path}, max_level{that.max_level}, min_level{that.min_level}{
    m_ofstream.open(m_file_path, std::ios_base::app);
}
file_appender::file_appender(log_level level, const std::string& file_path, log_level min_level) : max_level{level}, m_file_path{file_path}, min_level{min_level}{
    m_ofstream.open(file_path, std::ios_base::app);
}

void file_appender::log(const std::string& message, log_level log_level){
    if (log_level <= max_level && log_level >= min_level){
        m_ofstream << message << '\n';
    }
}

void logger::set_prefix(std::function<std::string(const std::string&)> prefix){
    m_prefix = prefix;
}

void logger::set_suffix(std::function<std::string(const std::string&)> suffix){
    m_suffix = suffix;
}

void logger::fatal(const std::string& message){
    log(message, log_level::FATAL);
}
void logger::error(const std::string& message){
    log(message, log_level::ERROR);
}
void logger::warn(const std::string& message){
    log(message, log_level::WARN);
}
void logger::info(const std::string& message){
    log(message, log_level::INFO);
}
void logger::debug(const std::string& message){
    log(message, log_level::DEBUG);
}
void logger::trace(const std::string& message){
    log(message, log_level::TRACE);
}

void logger::add_std_out_appender(const std_out_appender& appender){
    m_std_out_appenders.push_back(appender);
}
void logger::add_std_err_appender(const std_err_appender& appender){
    m_std_err_appenders.push_back(appender);
}
void logger::add_file_appender(const file_appender& appender){
    m_file_appenders.push_back(appender);
}

std::string logger::level_to_string(log_level level){
    return LEVEL_STRINGS.at(level);
}

void logger::log(const std::string& message, log_level level){
    std::string full_message = m_prefix(logger::level_to_string(level)) + message + m_suffix(logger::level_to_string(level));
    for (auto& appender : m_std_out_appenders){
        appender.log(full_message, level);
    }
    for (auto& appender : m_std_err_appenders){
        appender.log(full_message, level);
    }
    for (auto& appender : m_file_appenders){
        appender.log(full_message, level);
    }
}