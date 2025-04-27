#include "config.h"

int main(){
    tflib::ini_file config("test.ini", {
        {"", "yo", "val"}
    }, false);
    std::cout << config.get("yo") << '\n';
}