find_package(gRPC CONFIG REQUIRED)

get_target_property(PROTOC protobuf::protoc LOCATION)
get_target_property(GRPC_PLUGIN gRPC::grpc_cpp_plugin LOCATION)

file(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")

foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME)
    get_filename_component(PROTO_NAME_WE ${PROTO_FILE} NAME_WE)

    list(APPEND PROTO_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME_WE}.pb.cc")
    list(APPEND PROTO_HDRS "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME_WE}.pb.h")

    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME_WE}.pb.h" "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME_WE}.pb.cc"
        COMMAND ${PROTOC}
        ARGS
        -I${CMAKE_CURRENT_SOURCE_DIR}
        --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}
        ${PROTO_NAME}
        DEPENDS ${PROTO_FILE}
        COMMENT "Generating proroto sources for ${PROTO_NAME}"
    )

    list(APPEND GRPC_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME_WE}.grpc.pb.cc")
    list(APPEND GRPC_HDRS "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME_WE}.grpc.pb.h")

    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME_WE}.grpc.pb.h" "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME_WE}.grpc.pb.cc"
        COMMAND ${PROTOC}
        ARGS
        -I${CMAKE_CURRENT_SOURCE_DIR}
        --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}
        --plugin=protoc-gen-grpc=${GRPC_PLUGIN}
        --grpc_out=${CMAKE_CURRENT_SOURCE_DIR}
        ${PROTO_NAME}
        DEPENDS ${PROTO_FILE}
        COMMENT " Generating gRPC sources for ${PROTO_NAME} "
    )
endforeach()

add_custom_target(
    RpcGenerator ALL
    DEPENDS ${PROTO_SRCS} ${GRPC_SRCS}
    COMMENT " Generating proto and grpc files "
    VERBATIM
)