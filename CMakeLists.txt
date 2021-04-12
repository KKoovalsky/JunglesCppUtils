cmake_minimum_required(VERSION 3.16)

project(JunglesCppUtils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(jungles_cpp_utils INTERFACE)
target_include_directories(jungles_cpp_utils INTERFACE ${CMAKE_CURRENT_LIST_DIR})
add_library(jungles::cpp_utils ALIAS jungles_cpp_utils)

set(JUNGLES_CPP_UTILS_ENABLE_TESTING OFF CACHE BOOL "Enables self-testing of the library")
if(JUNGLES_CPP_UTILS_ENABLE_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
