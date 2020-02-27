cmake_minimum_required(VERSION 3.14)

set(sets_SRCS sets.hpp)
add_library(sets ${sets_SRCS})
set_target_properties(sets PROPERTIES LINKER_LANGUAGE CXX)