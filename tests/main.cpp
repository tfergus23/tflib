#include "config.h"

int main(){
    tflib::ini_file config("test.ini", {
        {"sect", "yo", "val"}
    }, false);
    std::cout << config.get_int("sect","yo") << '\n';
}