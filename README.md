# tflib
`tflib` is my (Thomas Fergus) own personal utils library for c++. Below you will find a description of each header as well as examples of how to use them.

## arg_parser.h
`tflib::arg_parser` provides an easy way to define and obtain command line arguments.
#### Command Example:
```bash
./arg_parser_example pos1val --optional optionalval -f
```
#### Code
```cpp
#include "tflib/arg_parser.h"

int main(int argc, char** argv){
    tflib::arg_parser args;

    args.add_positional_arg("position1", 0); 
    args.add_optional_arg("optional", 'o'); 
    args.add_flag("flag", 'f'); 

    args.parse(argc, argv);

    std::string position1 = args.get_positional_arg(0); // pos1val
    std::string optional = args.get_optional_arg("optional"); // optionalval
    bool flag = args.get_flag("flag"); // true
}   
```

## config.h
`config.h` provides a class for reading and retrieving values from an ini file.
#### config.ini
```ini
stringval=string
intval=55
[section]
sectionval=string2
```
#### Code
```cpp
#include "tflib/config.h"

int main(){
    tflib::ini_file config("./config.ini");

    std::string stringval = config.get("stringval"); // string
    int intval = config.get_int("intval"); // 55
    std::string sectionval = config.get("section", "sectionval"); // string2
}
```

## dotenv.h
`dotenv.h` provides a way to load a `.env` file into environment variables as well as a standard way of obtaining the value of environment variables.

#### .env
```ini
key1=val1
key2=val2
```
#### Code
```cpp
#include "tflib/dotenv.h"

int main(){
    tflib::load_dotenv();

    std::string val1 = tflib::get_env("key1"); // "val1"
    std::string val2 = tflib::get_env("key2"); // "val2"
    std::string val3 = tflib::get_env("key3"); // ""
}
```

## static_vector.h
`static_vector.h` provides a vector class with a similar interface to `std::vector`, but the capacity is fixed and known at compile time which allows it to be allocated on the stack.
#### Code
```cpp
#include "tflib/static_vector.h"

int main(){
    tflib::static_vector<int,5> vec;
    vec.push_back(1);
    vec.emplace_back(2);
    vec.push_back(3);
    
    int val = vec[1]; // 2
    vec.size(); // 3
    vec.clear();
    int val2 = vec[2]; // Throws in debug mode

    vec.push_back(1);
    vec.emplace_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6); // Throws in debug mode
}
```
## strings.h
`strings.h` provides various utility functions for working with strings
```cpp
#include "tflib/strings.h"
int main(){
    auto split = tflib::split("Hello there! Welcome to tflib!", " "); // {"Hello", "there!", "Welcome", "to", "tflib!"}

    std::string lower = tflib::to_lower("HELLO!"); // "hello!"

    std::string upper = tflib::to_upper("hello!"); // "HELLO!"

    std::string no_comment = tflib::remove_comment_from_line("This is a line of code # And this is a coment", "#"); // "This is a line of code "

    std::string trimmed = tflib::trim("            boy, it's roomy in here            "); // "boy, it's roomy in here"
}
```