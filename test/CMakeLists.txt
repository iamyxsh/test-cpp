add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest googletest)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/libs)
include_directories(${CMAKE_SOURCE_DIR}/third_party/json/single_include)

add_library(derbit_api ${CMAKE_SOURCE_DIR}/libs/derbit_api/derbit_api.cpp)
add_library(utils ${CMAKE_SOURCE_DIR}/libs/utils/utils.cpp)
add_library(http_client ${CMAKE_SOURCE_DIR}/libs/http_client/http_client.cpp)


add_executable(test_main test_main.cpp test_derbit_api.cpp)
target_link_libraries(test_main derbit_api utils http_client gtest gtest_main CURL::libcurl)

add_test(NAME DerbitAPITest COMMAND test_main)