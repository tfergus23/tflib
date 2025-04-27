#pragma once
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace tflib{
    struct default_value{
        std::string section;
        std::string key;
        std::string value;
    };

    class ini_file{
    public:
        /// @brief Loads ini file at file_path into memory.
        /// @param file_path Path to ini file
        /// @param watch_file Switch whether or not to reload the file each time a value is accessed.
        ini_file(const std::string& file_path, bool watch_file=true);
        ini_file(const std::string& file_path, const std::vector<default_value>& defaults, bool watch_file=true);
        //Wrapper for get("", key)
        const std::string& get(const std::string& key);
        //Gets the value for the key in the specified section. Throws runtime_exception if the section doesn't exist or the key doesn't exist in the section.
        const std::string& get(const std::string& section, const std::string& key);
        //Allows you to set default values for specified section/key/value pairs. Pairs specified in the ini file will take precedenced over these. Example:
        //
        //config.set_defaults({
        //    {"section1", "key1", "value1"},
        //    {"section2", "key2", "value2"},
        //    {"", "key", "value"},
        //});
        void set_defaults(const std::vector<default_value>& defaults);
        //Wrapper for has_key("", key)
        bool has_key(const std::string& key);
        //Returns true if the specified section/key pair exists in the ini file. Returns false otherwise.
        bool has_key(const std::string& section, const std::string& key);
        bool watch_file = false;
        void print() const;
    private:
        void read_file();
        void load_defaults();
        const std::string m_file_path;
        std::ifstream m_file;
        std::unordered_map<std::string,std::unordered_map<std::string,std::string>> m_map;
        std::vector<default_value> m_defaults;
    };
}

