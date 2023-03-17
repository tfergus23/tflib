#include <string>
#include "../include/strings.h"
#include "../include/logger.h"
#include <vector>
#include <map>
#include <fstream>
#include <cctype>

namespace tflib{
    const std::vector<std::string> split(const std::string &string, const unsigned char &delimitter){
        std::vector<std::string> strings;
        std::string element = "";
        for (int i = 0; i < string.length(); i++){
            if (string[i] == delimitter){
                strings.push_back(element);
                element = "";
            }
            else{
                element += string[i];
            }
        }
        strings.push_back(element);
        return strings;
    }

    std::string removeComment(const std::string &string, const unsigned char &commentChar){
        int commentCharPos = string.find(commentChar);
        return string.substr(0, commentCharPos);
    }

    std::string trim(const std::string &string){
        int start = string.find_first_not_of(WHITESPACE);
        if (start < 0 || string == "") return "";
        int end = string.find_last_not_of(WHITESPACE);
        int size = end - start + 1;
        return string.substr(start,size);
    }

    std::string toLower(const std::string &string){
        std::string result = "";
        for (unsigned char c : string){
            if (isalpha(c)){
                result += std::tolower(c);
            }
            else{
                result += c;
            }
        }
        return result;
    }
}