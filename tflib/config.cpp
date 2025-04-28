#include "config.h"
#include "strings.h"
#include <string>

using namespace tflib;

ini_file::ini_file(const std::string& file_path, bool watch_file) : m_file_path{file_path}, watch_file{watch_file}, m_file{file_path} {
    if (!m_file){
        throw std::runtime_error("File not found and no defaults supplied: " + file_path);
    }
    read_file();
}

ini_file::ini_file(const std::string& file_path, const std::vector<default_value>& defaults, bool watch_file) : m_file_path{file_path}, watch_file{watch_file}, m_defaults{defaults}, m_file{file_path}{
    read_file();
}

const std::string& ini_file::get(const std::string& section, const std::string& key){
    if (watch_file){
        read_file();
    }
    try{
        return m_map.at(section).at(key);
    } catch (const std::out_of_range& e){
        throw std::runtime_error("Key not found in " + m_file_path + ((section == "") ? "" : ", section " + section) + ": '" + key + "'");
    }
}

const std::string& ini_file::get(const std::string& key){
    return get("", key);
}

bool ini_file::has_key(const std::string& section, const std::string& key){
    if (m_map.count(section)){
        return m_map.at(section).count(key);
    }
    return false;
}

bool ini_file::has_key(const std::string& key){
    return has_key("", key);
}

bool line_is_section_definition(const std::string& line){
    return line.size() > 0 && line[0] == '[' && line[line.size()-1] == ']';
}

void ini_file::read_file(){

    int line_num = 1;
    m_map.clear();

    std::string current_section = "";
    load_defaults();

    if (!m_file){
        return;
    }

    for(std::string line; std::getline(m_file, line);){
        line = trim(remove_comment_from_line(line, "#"));
        if (line_is_section_definition(line)){
            current_section = trim(line.substr(1,line.size()-2));
            continue;
        }
        if (line != ""){
            int first_equals = line.find_first_of('=');
            if (first_equals == std::string::npos){
                continue;
            }
            std::string key = line.substr(0, first_equals);
            std::string val = line.substr(first_equals+1, line.size());
            m_map[current_section][trim(key)] = trim(val);
        }

        line_num++;
    }
    if (!watch_file){
        m_file.close();
    }
}

void ini_file::print() const{
    for (auto& [section, map] : m_map){
        std::cout << "[" << section << "]\n";
        for(auto& [key,val] : map){
            std::cout << "'" << key  <<"'" << ": '" << val <<"'" << '\n';
        }
    }

}

void ini_file::set_defaults(const std::vector<default_value>& defaults){
    m_defaults = defaults;
    read_file();
}

void ini_file::load_defaults(){
    for (auto& def : m_defaults){
        m_map[def.section][def.key] = def.value;
    }
}

int32_t ini_file::get_int(const std::string& key){
    return get_int("", key);
}
int32_t ini_file::get_int(const std::string& section, const std::string& key){
    const auto& str = get(section, key);
    try{
        return stoi(str);
    }
    catch(...){
        throw std::runtime_error("Invalid value for " + (section != "" ?  section + "." : "") + key + " in " + m_file_path + ". Expected a signed 32-bit integer, got '" + str + "'");
    }
}