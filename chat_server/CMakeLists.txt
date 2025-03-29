cmake_minimum_required(VERSION 3.15.0)
project(ChatServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE MESSAGES_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cc")

add_subdirectory(src/messages)
add_executable(ChatServer ${SOURCES} ${MESSAGES_SOURCES})
add_dependencies(ChatServer RpcGenerator)

file(COPY_FILE config.ini ${CMAKE_BINARY_DIR}/config.ini)

find_package(Boost REQUIRED COMPONENTS asio beast property_tree)
find_package(jsoncpp CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(hiredis CONFIG REQUIRED)
find_package(unofficial-mysql-connector-cpp CONFIG REQUIRED)
target_link_libraries(ChatServer PRIVATE
    Boost::asio Boost::beast Boost::property_tree
    JsonCpp::JsonCpp fmt::fmt gRPC::grpc++ hiredis::hiredis
    unofficial::mysql-connector-cpp::connector unofficial::mysql-connector-cpp::connector-jdbc
    unofficial::libmysql::libmysql
)