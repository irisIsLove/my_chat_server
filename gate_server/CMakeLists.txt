cmake_minimum_required(VERSION 3.15.0)
project(GateServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(GateServer ${SOURCES})

find_package(Boost REQUIRED COMPONENTS asio beast)
find_package(jsoncpp CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(GateServer PRIVATE Boost::asio Boost::beast JsonCpp::JsonCpp fmt::fmt)