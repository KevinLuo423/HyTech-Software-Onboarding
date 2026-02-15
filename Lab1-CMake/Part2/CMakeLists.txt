cmake_minimum_required(VERSION 3.15)

project(Lab1.5 VERSION 1.0
            DESCRIPTION "harder version of the other one"
            LANGUAGES CXX)


add_library(hello_lib STATIC src/hello_world.cpp include/hello_world.hpp)   
target_include_directories(hello_lib PUBLIC include)

add_executable(hello src/main.cpp)
target_link_libraries(hello PUBLIC hello_lib)