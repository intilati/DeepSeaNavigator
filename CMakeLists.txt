cmake_minimum_required(VERSION 3.10)
project(DeepSeaNavigator)

set(CMAKE_CXX_STANDARD 17)

#Source files
set(
	src/main.CPP
	src/GridMap.CPP
)

#Main executable 
add_executable(DeepSeaNavigator ${src})

#Testing setup
enable_testing()
add_executable(test_basic tests/test_basic.cpp src?GridMap.cpp)
add_test(NAME basic_test COMMAND test_basic)
