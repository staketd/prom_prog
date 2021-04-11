cmake_minimum_required(VERSION 3.10)
project(Task2 CXX)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE C/main.cpp C/main.hpp)
include_directories(.)

find_package(GTest)

add_custom_command(
        OUTPUT A/index.hpp
        COMMAND python3 A/preparing.py
)

include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_BUILD_FILES_DIRECTORY build)
set(CMAKE_BUILD_DIRECTORY build)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_target(RunGenerator DEPENDS A/index.hpp)

add_executable(runTests C/main_test.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

add_library(index SHARED A/index.hpp)
SET_TARGET_PROPERTIES(index PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(B)
add_executable(Task2 ${SOURCE})

add_dependencies(Task2 RunGenerator)