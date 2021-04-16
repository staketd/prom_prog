cmake_minimum_required(VERSION 3.19)
project(CodeGen)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/codegen.hpp
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/generate_header.py ${IMAGE_PATH}
)

add_library(generated SHARED codegen.hpp)
set_target_properties(generated PROPERTIES LINKER_LANGUAGE CXX)

add_custom_target(RunGenerator DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/codegen.hpp)

add_executable(CodeGen codegen.cpp)

add_executable(OpenCV opencv.cpp)
add_dependencies(CodeGen RunGenerator)

target_link_libraries(OpenCV ${OpenCV_LIBS})
target_link_libraries(CodeGen ${OpenCV_LIBS})