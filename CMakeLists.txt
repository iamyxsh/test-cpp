project(TradingBot)


enable_testing()


set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0
)
FetchContent_MakeAvailable(fmt)


find_package(CURL REQUIRED)

include_directories(third_party/json/single_include)


add_library(derbit_api libs/derbit_api/derbit_api.cpp)
add_library(utils libs/utils/utils.cpp)
add_library(http_client libs/http_client/http_client.cpp)


add_executable(main main.cpp)
target_link_libraries(main derbit_api util fmt::fmt http_client CURL::libcurl)


add_subdirectory(test)