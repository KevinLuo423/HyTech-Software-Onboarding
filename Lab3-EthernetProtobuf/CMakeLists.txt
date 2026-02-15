cmake_minimum_required(VERSION 3.15)

project(Lab3 VERSION 1.0
            DESCRIPTION "protobuf"
            LANGUAGES CXX)

find_package(Protobuf REQUIRED)

# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS simpleMessage.proto)

add_executable(start_client src/client.cpp include/simpleMessage.pb.cc)
target_include_directories(start_client PRIVATE
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    include
)
add_executable(start_server src/server.cpp include/simpleMessage.pb.cc)
target_include_directories(start_server PRIVATE 
    ${PROTOBUF_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_BINARY_DIR}
    include
)

target_link_libraries(start_client PRIVATE ${PROTOBUF_LIBRARIES})
target_link_libraries(start_server PRIVATE ${PROTOBUF_LIBRARIES})

install(TARGETS start_client start_server DESTINATION bin)