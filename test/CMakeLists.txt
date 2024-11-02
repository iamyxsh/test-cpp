# Find GTest
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest googletest)

find_package(CURL REQUIRED)

# Include directories for libraries
include_directories(${CMAKE_SOURCE_DIR}/libs/derbit_api)
include_directories(${CMAKE_SOURCE_DIR}/libs/utils)
include_directories(${CMAKE_SOURCE_DIR}/libs/http_client)


# Add librarie

# Add test executable
add_executable(test_main test_main.cpp)
target_link_libraries(test_main derbit_api utils http_client gtest gtest_main CURL::libcurl)

# Add tests
add_test(NAME TESTS COMMAND test_main)