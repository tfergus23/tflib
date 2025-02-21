cmake_minimum_required(VERSION 3.22)

project("TFLib")

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include/tflib)

add_library(TFLib tflib/config.cpp tflib/logger.cpp tflib/strings.cpp)