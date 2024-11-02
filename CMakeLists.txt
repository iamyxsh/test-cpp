project(TradingBot)

enable_testing()

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)

include_directories(third_party/json/single_include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/fmt/include)
include_directories(${CMAKE_SOURCE_DIR}/libs)

add_library(derbit_api libs/derbit_api/derbit_api.cpp)
add_library(utils libs/utils/utils.cpp)
add_library(http_client libs/http_client/http_client.cpp)

add_executable(main main.cpp)
target_link_libraries(main http_client derbit_api utils CURL::libcurl)

add_subdirectory(test)