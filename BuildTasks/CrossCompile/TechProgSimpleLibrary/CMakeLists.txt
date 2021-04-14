cmake_minimum_required(VERSION 3.0)
project(SimpleLibrary)

include_directories(include)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SimpleLibrary_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SimpleLibrary_SOURCE_DIR}/lib)


set(arm_tools /home/pushind/Downloads/gcc-linaro-7.5.0-2019.12-i686_arm-linux-gnueabihf/bin)

add_subdirectory(src)
add_executable(Main main.cpp)
add_executable(MainLib main_lib.cpp)

target_link_libraries(MainLib buffer)

message(INFO ${INSTALL_DIR})


set_target_properties(
	MainLib
	PROPERTIES
	INSTALL_RPATH ${INSTALL_DIR}/lib
)
set_target_properties(
	Main
	PROPERTIES
	INSTALL_RPATH ${INSTALL_DIR}/lib
)

install(
	TARGETS Main
	DESTINATION ${INSTALL_DIR}/bin
)

install(
	TARGETS MainLib
	DESTINATION ${INSTALL_DIR}/bin
)

install(
	TARGETS buffer
	DESTINATION ${INSTALL_DIR}/lib
)
