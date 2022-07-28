#pragma once
#include <map>
#include <string>

namespace tflib{
    static std::map<std::string,std::string> iniMap;
    void readIniFile(const std::string &fileName);
    std::string getIniVar(const std::string &varName);
}