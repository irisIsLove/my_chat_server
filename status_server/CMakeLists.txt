cmake_minimum_required(VERSION 3.15.0)
project(StatusServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE MESSAGES_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cc")
list(APPEND SOURCES ${MESSAGES_SOURCES})

add_subdirectory(src/messages)
add_executable(StatusServer ${SOURCES})

add_dependencies(StatusServer RpcGenerator)
file(COPY_FILE config.ini ${CMAKE_BINARY_DIR}/config.ini)
find_package(Boost REQUIRED COMPONENTS asio beast property_tree uuid)
find_package(gRPC CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(hiredis CONFIG REQUIRED)
target_link_libraries(StatusServer PRIVATE
    Boost::asio Boost::property_tree Boost::uuid
    fmt::fmt gRPC::grpc++ hiredis::hiredis
)