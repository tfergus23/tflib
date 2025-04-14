#pragma once
#include <string>
#include <vector>
#include <map>

namespace tflib{
    std::vector<std::string> split(const std::string &string, const std::string& delimitter);
    std::vector<std::string_view> split_views(std::string_view string, std::string delimitter);
    std::string remove_comment_from_line(const std::string &line, const std::string& comment_str = "#");
    std::string trim(const std::string &string);
    std::string to_lower(const std::string &string);
    std::string to_upper(const std::string &string);
}