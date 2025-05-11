#include "config.h"

int main(){
    tflib::ini_file config("test.ini",{
        {"", "password", "hello"},
    }, true);
    for (std::string line; std::getline(std::cin, line);){
        std::cout << config.get("password") << '\n';
    }
}