cmake_minimum_required(VERSION 3.10)
project(DeepSeaNavigator)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

add_executable(DeepSeaNavigator
    src/main.cpp
    src/gridmap.cpp
)

