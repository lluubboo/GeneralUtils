cmake_minimum_required(VERSION 3.5.0)
project(CustomUtils VERSION 0.0.1 LANGUAGES CXX)

# set C++ standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(CMAKE_BUILD_TYPE Debug)

if (CMAKE_BUILD_TYPE STREQUAL "Debug") 

    # enable warnings, ...
    add_compile_options(-Wall -Wpedantic -Wextra -fexceptions -Weffc++)

    # run tests only in debug mode
    add_subdirectory(test)
    include(CTest)

elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-march=native)
endif()

add_subdirectory(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


