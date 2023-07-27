#include <string>
#include "strings.h"
#include <vector>
#include <map>
#include <fstream>
#include <cctype>
#include <iostream>

const std::string WHITESPACE = " \n\r\t\f\v";

void tflib::split(const std::string &string, const std::string& delimitter, std::vector<std::string>& out){
    int start = 0;
    int next = 0;
    while (start < string.size()){
        next = string.find(delimitter, start);
        if (next == std::string::npos){
            next = string.size();
        }
        out.push_back(string.substr(start, string.size() - start - (string.size() - next)));
        start = next + delimitter.size();
    }
    if (next == string.size() - delimitter.size()){
        out.push_back("");
    }
}
std::string tflib::remove_comment_from_line(const std::string &line, const std::string& comment_str){
    return line.substr(0, line.find(comment_str));
}
std::string tflib::trim(const std::string &string){
    if (string.empty()){
        return "";
    }
    int begin = string.find_first_not_of(WHITESPACE);
    if (begin == std::string::npos){
        return "";
    }
    int end = string.find_last_not_of(WHITESPACE) + 1;
    int size = end - begin;
    return string.substr(begin, size);
}
std::string tflib::to_lower(const std::string &string){
    std::string result = "";
    result.reserve(string.size());
    for (char c : string){
        result += tolower(c);
    }
    return result;
}

std::string tflib::to_upper(const std::string &string){
    std::string result = "";
    result.reserve(string.size());
    for (char c : string){
        result += toupper(c);
    }
    return result;
}