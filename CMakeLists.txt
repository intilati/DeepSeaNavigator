cmake_minimum_required(VERSION 3.10)
project(voxnav)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

add_executable(voxnav
    src/main.cpp
    src/gridmap.cpp
    src/AStarPlanner.cpp
    )
# Copy config folder to build directory
file(COPY ${CMAKE_SOURCE_DIR}/config DESTINATION ${CMAKE_BINARY_DIR})


# simple GridMap test
if(EXISTS "${CMAKE_SOURCE_DIR}/tests/test_gridmap.cpp")
  enable_testing()
  add_executable(test_gridmap
      tests/test_gridmap.cpp
      src/gridmap.cpp
      src/AStarPlanner.cpp
  )
  set_target_properties(test_gridmap PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )

  add_test(NAME gridmap_test COMMAND test_gridmap)
endif()

# edgecases test
if (EXISTS "${CMAKE_SOURCE_DIR}/tests/test_edgecases.cpp")
    enable_testing()
    add_executable(test_edgecases tests/test_edgecases.cpp src/gridmap.cpp src/AStarPlanner.cpp)
    set_target_properties(test_edgecases PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)

    add_test(NAME EdgeCasesTest COMMAND test_edgecases)
endif()

# A* test 
if (EXISTS "${CMAKE_SOURCE_DIR}/tests/test_astar.cpp")
    enable_testing()
    add_executable(test_astar
        tests/test_astar.cpp
        src/gridmap.cpp
        src/AStarPlanner.cpp
    )
    set_target_properties(test_astar PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )

    add_test(NAME AStarTest COMMAND test_astar)
endif()






