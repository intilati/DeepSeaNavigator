cmake_minimum_required(VERSION 3.10)
project(DeepSeaNavigator)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

add_executable(DeepSeaNavigator
    src/main.cpp
    src/gridmap.cpp
    src/AStarPlanner.cpp
)

# simple optional test target (only created if the test file exists)
if(EXISTS "${CMAKE_SOURCE_DIR}/tests/test_gridmap.cpp")
  enable_testing()
  add_executable(test_gridmap
      tests/test_gridmap.cpp
      src/gridmap.cpp
      src/AStarPlanner.cpp
  )
  add_test(NAME gridmap_test COMMAND test_gridmap)
endif()


