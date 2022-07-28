#include "config.h"
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>

namespace tflib{

    void readIniFile(const std::string &fileName){
        std::fstream iniFileStream;
        iniFileStream.open(fileName, std::ios::in);
        std::string line;
        if (!iniFileStream.is_open()){
            throw std::exception("Could not open INI file");
        }
        while (getline(iniFileStream, line)){
            std::string key = "";
            std::string val = "";
            int i = 0;
            bool foundEquals = false;
            while (i < line.length()){
                if (line[i] == '='){
                    i++;
                    foundEquals = true;
                    break;
                }
                key += line[i];
                i++;
            }
            if (!foundEquals){
                throw std::exception("Malformed INI file: no equals sign found");
            }
            if (iniMap.count(key)){
                throw std::exception("Duplicate INI variable found");
            }
            while (i < line.length()){
                val += line[i];
                i++;
            }
            iniMap.insert(std::pair<std::string,std::string>(key,val));
        }
        iniFileStream.close();
    }

    std::string getIniVar(const std::string &varName){
        return iniMap[varName];
    }
}

