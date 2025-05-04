cmake_minimum_required(VERSION 3.22)

project("TFLib")

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Werror -Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include/tflib)

add_library(TFLib tflib/config.cpp tflib/logger.cpp tflib/strings.cpp tflib/arg_parser.cpp tflib/dotenv.cpp)
if (TFLIB_TESTS)
    add_executable(tftests tests/main.cpp)
    target_link_libraries(tftests TFLib)
endif()