
project(tree)

add_executable(tree main.cpp Graph.hpp lsis.cpp)
target_include_directories(tree PUBLIC ../lib)
target_link_libraries(tree sets)



