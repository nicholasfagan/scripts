cmake_minimum_required(VERSION 3.14)

find_package(Threads REQUIRED)
set(test_SRCS test.cpp test.h)
add_executable(tests ${test_SRCS})
target_include_directories(tests PUBLIC ../lib)
target_link_libraries(tests sets ${CMAKE_THREAD_LIBS_INIT})
