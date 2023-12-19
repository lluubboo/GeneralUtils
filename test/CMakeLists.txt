cmake_minimum_required(VERSION 3.5.0)
project(CustomUtilsTests VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

# add the Google Test install directory 
list(APPEND CMAKE_PREFIX_PATH "c:/Users/lubomir.balaz/SWLibraries/googletest-1.14.0-install")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS} ../include)

add_executable(runTests testLRUCache.cpp testThreadSafeContainer.cpp)

target_link_libraries(runTests ${GTEST_BOTH_LIBRARIES})

enable_testing()

add_test(NAME CustomUtilsTests COMMAND runTests)