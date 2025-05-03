#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

namespace tflib{
    class arg_parser{
        public:
            void add_optional_arg(const std::string& name, char shorthand);
            void add_positional_arg(std::string_view name, uint32_t position);
            void add_flag(const std::string& name, char shorthand);
        
            std::string get_optional_arg(const std::string& name) const;
            std::string get_positional_arg(uint32_t position) const;
            bool get_flag(const std::string& name) const;
        
            std::string parse(int argc, char** argv);
        private:
            std::unordered_map<std::string, std::string> m_optional_args;
            std::unordered_map<char, std::string> m_shorthands;
            std::unordered_set<std::string> m_flag_names;
            std::unordered_set<std::string> m_set_flags;
            std::vector<std::string> m_positional_arg_values;
            std::vector<std::string> m_positional_arg_names;
    };
}

