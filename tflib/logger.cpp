#include "include/logger.h"
using namespace tflib;

std::string logger::get_prefix(){
    return m_prefix;
}
void logger::set_prefix(const std::string& prefix){
    m_prefix = prefix;
}

std::string logger::get_suffix(){
    return m_suffix;
}
void logger::set_suffix(const std::string& suffix){
    m_suffix = suffix;
}

void logger::fatal(const std::string& message){
    if (level >= log_level::FATAL){
        log(message);
    }
}
void logger::error(const std::string& message){
    if (level >= log_level::ERROR){
        log(message);
    }
}
void logger::warn(const std::string& message){
    if (level >= log_level::WARN){
        log(message);
    }
}
void logger::info(const std::string& message){
    if (level >= log_level::INFO){
        log(message);
    }
}
void logger::debug(const std::string& message){
    if (level >= log_level::DEBUG){
        log(message);
    }
}
void logger::trace(const std::string& message){
    if (level >= log_level::TRACE){
        log(message);
    }
}

void logger::log(const std::string& message){
    std::cout << m_prefix << message << m_suffix << '\n';
}