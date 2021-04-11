project(inner CXX)

include_directories(.)

add_library(lb SHARED lib.hpp)
SET_TARGET_PROPERTIES(lb PROPERTIES LINKER_LANGUAGE CXX)