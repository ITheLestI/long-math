cmake_minimum_required(VERSION 3.12)

project(
    labwork2
    VERSION 1.0
    DESCRIPTION "C++ Year 2023 Labwork2"
    LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)
