#pragma once
#include <string>
#include <vector>
#include <map>

namespace tflib{
    void split(const std::string &string, const std::string& delimitter, std::vector<std::string>& out);
    std::string remove_comment_from_line(const std::string &line, const std::string& comment_str = "#");
    std::string trim(const std::string &string);
    std::string to_lower(const std::string &string);
}