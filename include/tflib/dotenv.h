#include <string>

namespace tflib{
    bool load_dotenv();
    bool load_dotenv(const char* path_to_env_file);

    std::string get_env(std::string_view name);
}
