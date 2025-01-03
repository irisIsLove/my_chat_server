cmake_minimum_required(VERSION 3.15.0)
project(GateServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE MESSAGES_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cc")
list(APPEND SOURCES ${MESSAGES_SOURCES})
message(STATUS "SOURCES: ${SOURCES}")

add_subdirectory(src/messages)
add_executable(GateServer ${SOURCES})

file(COPY_FILE config.ini ${CMAKE_BINARY_DIR}/config.ini)

find_package(Boost REQUIRED COMPONENTS asio beast property_tree)
find_package(jsoncpp CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(GateServer PRIVATE
    Boost::asio Boost::beast Boost::property_tree
    JsonCpp::JsonCpp fmt::fmt gRPC::grpc++)