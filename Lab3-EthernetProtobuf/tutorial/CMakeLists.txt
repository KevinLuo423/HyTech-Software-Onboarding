cmake_minimum_required(VERSION 3.15)

project(protobufLab VERSION 1.0
            DESCRIPTION "Lab3"
            LANGUAGES CXX)

find_package(Protobuf REQUIRED)

add_executable(protobuf_writer writer.cpp addressbook.pb.cc)
target_include_directories(protobuf_writer PRIVATE
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(protobuf_writer PRIVATE ${PROTOBUF_LIBRARIES})

add_executable(protobuf_reader reader.cpp addressbook.pb.cc)
target_include_directories(protobuf_reader PRIVATE
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(protobuf_reader PRIVATE ${PROTOBUF_LIBRARIES})

install(TARGETS protobuf_writer DESTINATION bin)

install(TARGETS protobuf_reader DESTINATION bin)