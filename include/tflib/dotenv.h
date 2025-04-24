#include <string>

namespace tflib{
    void load_dotenv();
    void load_dotenv(const char* path_to_env_file);

    std::string get_env(std::string_view name);
}
