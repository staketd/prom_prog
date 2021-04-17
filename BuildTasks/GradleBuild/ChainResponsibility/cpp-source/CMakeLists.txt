cmake_minimum_required(VERSION 3.5)
project(ChainResponsibility)


set(CMAKE_CXX_STANDARD 14)
set(
    SOURCES
        src/main/cpp/LogLevel.cpp
        src/main/cpp/LoggingHandler.cpp
        src/main/cpp/BaseHandler.cpp
        src/main/cpp/DivisionZeroHandler.cpp
        src/main/cpp/FileHandler.cpp src/main/headers/FileHandler.h src/main/cpp/StderrHandler.cpp src/main/headers/StderrHandler.h)

add_executable(ChainResponsibility ${SOURCES} src/main/cpp/main.cpp)