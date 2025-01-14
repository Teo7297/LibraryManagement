cmake_minimum_required(VERSION 3.20)
project(LibraryManagementSystem VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
    rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG        v1.1.0
)
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "" FORCE)  # Disable tests
FetchContent_MakeAvailable(rapidjson)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(LibraryManagementSystem ${SOURCES})

target_include_directories(LibraryManagementSystem PRIVATE include ${rapidjson_SOURCE_DIR}/include)
