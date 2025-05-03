#include "../include/tflib/arg_parser.h"
#include <stdexcept>
#include <iostream>

using namespace tflib;

void arg_parser::add_optional_arg(const std::string& name, char shorthand){
    m_optional_args[name];
    m_shorthands[shorthand] = name;
}
void arg_parser::add_positional_arg(std::string_view name, uint32_t position){
    if (position != m_positional_arg_names.size()){
        throw std::runtime_error("Tried to add positional arg at index " + std::to_string(position) + ", expected index: " + std::to_string(m_positional_arg_names.size()));
    }
    m_positional_arg_names.emplace_back(name.data(), name.size());
}
void arg_parser::add_flag(const std::string& name, char shorthand){
    m_flag_names.insert(name);
    m_shorthands[shorthand] = name;
}

std::string arg_parser::get_optional_arg(const std::string& name) const{
    if (!m_optional_args.contains(name)){
        return "";
    }
    return m_optional_args.at(name);
}
std::string arg_parser::get_positional_arg(uint32_t position) const{
    if (position < m_positional_arg_values.size()){
        return m_positional_arg_values[position];
    }
    return "";
}
bool arg_parser::get_flag(const std::string& name) const{
    return m_set_flags.contains(name);
}

std::string arg_parser::parse(int argc, char** argv){
    uint32_t positional_index = 0;
    std::string last_optional_arg_found = "";
    for (int i = 1; i < argc; ++i){
        std::string arg = argv[i];

        std::string arg_name = "";
        bool is_optional = false;

        if (arg.size() >= 2 && arg.substr(0,2) == "--"){
            arg_name = arg.substr(2,arg.size()-2);
            is_optional = true;
        }
        else if (arg.size() >= 1 && arg[0] == '-'){
            if (arg.size() != 2){
                return "Invalid shorthand argument: '" + arg + "'";
            }
            if (!m_shorthands.contains(arg[1])){
                return "Unknown shorthand argument: '" + arg + "'";
            }
            arg_name = m_shorthands[arg[1]];
            is_optional = true;
        }
        else {
            if (last_optional_arg_found == "" && positional_index >= m_positional_arg_names.size()){
                return "Unexpected positional argument '" + arg + "' at position "  + std::to_string(positional_index);
            }
            arg_name = arg;
        }

        if (is_optional){
            if (last_optional_arg_found != ""){
                return "No value provided for optional argument '" + last_optional_arg_found + "'";
            }

            if (m_flag_names.contains(arg_name)){
                m_set_flags.insert(arg_name);
            }
            else if (m_optional_args.contains(arg_name)){
                last_optional_arg_found = arg_name;
            }
            else{
                return "Unknown optional argument provided: '" + arg_name + "'";
            }
        }
        else{
            if (last_optional_arg_found != ""){
                m_optional_args[last_optional_arg_found] = arg_name;
                last_optional_arg_found = "";
            }
            else{
                m_positional_arg_values.push_back(arg_name);
                positional_index++;
            }
        }
    }
    if (positional_index < m_positional_arg_names.size()){
        return "Missing positional argument '" + m_positional_arg_names[positional_index] + "' at position " + std::to_string(positional_index);
    }
    if (last_optional_arg_found != ""){
        return "No value provided for optional argument '" + last_optional_arg_found + "'";
    }
    return "";
}