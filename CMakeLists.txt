cmake_minimum_required(VERSION 3.22)

project("TFLib")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(TFLib tflib/config.cpp tflib/logger.cpp tflib/strings.cpp)