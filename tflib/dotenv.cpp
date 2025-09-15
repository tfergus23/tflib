#include "../include/tflib/dotenv.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "strings.h"

bool tflib::load_dotenv(){
    return load_dotenv("./.env");
}

bool tflib::load_dotenv(const char* path_to_env_file){
    std::ifstream file(path_to_env_file);

    if(!file.good()){
        std::cerr << "Couldn't open env file: " + std::string(path_to_env_file) << '\n';
        return false;
    }

    for (std::string line; std::getline(file, line);){
        line = tflib::trim(tflib::remove_comment_from_line(line, "#"));
        size_t equals = line.find("=");
        if (equals == std::string::npos){
            continue;
        }

        std::string name = line.substr(0,equals);
        std::string value = line.substr(equals+1, line.size()-equals);
#ifdef __linux__
        setenv(name.c_str(), value.c_str(), 1);
#endif
#ifdef _WIN32
        SetEnvironmentVariable(name.c_str(), value.c_str());
#endif
    }
    return true;
}

std::string tflib::get_env(std::string_view name) {
    const char* value = nullptr;

#ifdef __linux__
    value = getenv(name.data());
#endif

#ifdef _WIN32
    char* buffer = nullptr;
    size_t len = 0;
    if (_dupenv_s(&buffer, &len, name.data()) == 0 && buffer != nullptr) {
        value = buffer;
    }
#endif

    std::string result;
    if (value) {
        result = value;
    }

#ifdef _WIN32
    if (buffer) {
        free(buffer); // Free the memory allocated by _dupenv_s
    }
#endif

    return result;
}