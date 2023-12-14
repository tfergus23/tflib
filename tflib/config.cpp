#include "config.h"
#include "strings.h"
#include <string>

using namespace tflib;

ini_file::ini_file(const std::string& file_path, bool watch_file) : m_file_path{file_path}, watch_file{watch_file} {
    read_file();
}
const std::string& ini_file::get(const std::string& key){
    if (watch_file){
        read_file();
    }
    try{
        return m_map.at(key);
    } catch (const std::out_of_range& e){
        throw std::runtime_error("Key not found in " + m_file_path + ": '" + key + "'");
    }
}
bool ini_file::has_key(const std::string& key){
    return m_map.count(key);
}

void ini_file::read_file(){
    std::ifstream in_file(m_file_path);

    if (!in_file.is_open()){
        throw std::runtime_error("File not found: " + m_file_path);
    }

    int line_num = 1;
    m_map.clear();

    for(std::string line; std::getline(in_file, line);){
        line = trim(remove_comment_from_line(line, "#"));
        if (line != ""){
            int first_equals = line.find_first_of('=');
            if (first_equals == std::string::npos){
                continue;
            }
            std::string key = line.substr(0, first_equals);
            std::string val = line.substr(first_equals+1, line.size());
            m_map[trim(key)] = trim(val);
        }

        line_num++;
    }
}

void ini_file::print() const{
    for(auto& [key,val] : m_map){
        std::cout << "'" << key  <<"'" << ": '" << val <<"'" << '\n';
    }
}