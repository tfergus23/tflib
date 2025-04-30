#include "../include/tflib/dotenv.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#endif

void tflib::load_dotenv(){
    load_dotenv("./.env");
}

void tflib::load_dotenv(const char* path_to_env_file){
    std::ifstream file(path_to_env_file);

    if(!file.good()){
        std::cerr << "Couldn't open env file: " + std::string(path_to_env_file) << '\n';
        return;
    }

    for (std::string line; std::getline(file, line);){
        size_t equals = line.find("=");
        if (equals == std::string::npos){
            continue;
        }

        std::string name = line.substr(0,equals);
        std::string value = line.substr(equals+1, line.size()-equals);
#ifdef __LINUX__
        setenv(name.c_str(), value.c_str(), 1);
#endif
#ifdef _WIN32
        SetEnvironmentVariable(name.c_str(), value.c_str());
#endif
    }
}

std::string tflib::get_env(std::string_view name){
    const char* value = getenv(name.data());
    if (value){
        return value;
    }
    return "";
}