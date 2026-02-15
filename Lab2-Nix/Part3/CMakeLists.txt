cmake_minimum_required(VERSION 3.16)

project(helloappLab VERSION 1.0
            DESCRIPTION "part2"
            LANGUAGES CXX)


# add_library(hellolib STATIC src/hellolib.cpp include/hellolib.hpp)   
# target_include_directories(hellolib PUBLIC include)

find_package(hellolib CONFIG REQUIRED)

add_executable(hello main.cpp)

target_link_libraries(hello PRIVATE hellolib::hellolib)

install(TARGETS hello DESTINATION bin)