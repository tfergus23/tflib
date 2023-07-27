#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <unordered_map>

namespace tflib{
    class ini_file{
    public:
        ini_file(const std::string& file_path, bool watch_file=false);
        std::string get(const std::string& key);
        bool has_key(const std::string& key);
        bool watch_file = false;
    private:
        void read_file();
        const std::string m_file_path;
        std::unordered_map<std::string,std::string> m_map;
    };
}

