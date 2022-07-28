#pragma once
#include <string>
#include <vector>
#include <map>

namespace tflib{
    const std::string WHITESPACE = " \n\r\t\f\v";
    const std::vector<std::string> split(const std::string &string, const unsigned char &delimitter);
    std::string removeComment(const std::string &string, const unsigned char &commentChar='#');
    std::string trim(const std::string &string);
    std::string toLower(const std::string &string);
}