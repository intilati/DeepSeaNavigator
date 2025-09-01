# CMake generated Testfile for 
# Source directory: C:/Users/Dastagir/DeepSeaNavigator
# Build directory: C:/Users/Dastagir/DeepSeaNavigator/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(gridmap_test "C:/Users/Dastagir/DeepSeaNavigator/build/Debug/test_gridmap.exe")
  set_tests_properties(gridmap_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Dastagir/DeepSeaNavigator/CMakeLists.txt;21;add_test;C:/Users/Dastagir/DeepSeaNavigator/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(gridmap_test "C:/Users/Dastagir/DeepSeaNavigator/build/Release/test_gridmap.exe")
  set_tests_properties(gridmap_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Dastagir/DeepSeaNavigator/CMakeLists.txt;21;add_test;C:/Users/Dastagir/DeepSeaNavigator/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(gridmap_test "C:/Users/Dastagir/DeepSeaNavigator/build/MinSizeRel/test_gridmap.exe")
  set_tests_properties(gridmap_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Dastagir/DeepSeaNavigator/CMakeLists.txt;21;add_test;C:/Users/Dastagir/DeepSeaNavigator/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(gridmap_test "C:/Users/Dastagir/DeepSeaNavigator/build/RelWithDebInfo/test_gridmap.exe")
  set_tests_properties(gridmap_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Dastagir/DeepSeaNavigator/CMakeLists.txt;21;add_test;C:/Users/Dastagir/DeepSeaNavigator/CMakeLists.txt;0;")
else()
  add_test(gridmap_test NOT_AVAILABLE)
endif()
