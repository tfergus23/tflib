#include "dotenv.h"
#include <vector>
#include <iostream>

int main(){
    bool success = tflib::load_dotenv();


    if (success) std::cout << tflib::get_env("yo") << '\n';
}