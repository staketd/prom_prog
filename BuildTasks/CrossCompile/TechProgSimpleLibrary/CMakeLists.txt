cmake_minimum_required(VERSION 3.0)
project(SimpleLibrary)

include_directories(include)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SimpleLibrary_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SimpleLibrary_SOURCE_DIR}/lib)

set(arm_tools /home/pushind/Downloads/gcc-linaro-7.5.0-2019.12-i686_arm-linux-gnueabihf/bin)
set(CMAKE_C_COMPILER ${arm_tools}/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${arm_tools}/arm-linux-gnueabihf-g++)

add_subdirectory(src)
add_executable(Main main.cpp)
add_executable(MainLib main_lib.cpp)

target_link_libraries(MainLib buffer)


set_target_properties(
	MainLib
	PROPERTIES
	INSTALL_RPATH ${SimpleLibrary_SOURCE_DIR}/lib
)
set_target_properties(
	Main
	PROPERTIES
	INSTALL_RPATH ${SimpleLibrary_SOURCE_DIR}/lib
)

install(
	TARGETS Main
	DESTINATION /home/pushind/private/bin
)

install(
	TARGETS MainLib
	DESTINATION /home/pushind/private/bin
)
