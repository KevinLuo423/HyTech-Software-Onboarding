cmake_minimum_required(VERSION 3.15)

project(Lab2 VERSION 1.0
            DESCRIPTION "nix"
            LANGUAGES CXX)


add_library(hellolib STATIC src/hellolib.cpp include/hellolib.hpp)   
target_include_directories(hellolib PUBLIC include)

add_executable(hello src/main.cpp)
target_link_libraries(hello PUBLIC hellolib)

install(TARGETS hello DESTINATION bin)