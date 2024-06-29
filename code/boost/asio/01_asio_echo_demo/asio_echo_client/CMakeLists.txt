cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 指定项目名字和版本
project(asio_echo_client VERSION 0.1.0)

# 搜索第一个参数所指定的文件夹，将搜索的结果通过SRC_SUB传出
aux_source_directory(src SRC_SUB)
aux_source_directory(. SRC_CUR)
aux_source_directory(proto PROTO_SUB)

# 添加头文件目录
include_directories(./include)

add_executable(${PROJECT_NAME} ${SRC_SUB} ${SRC_CUR} ${PROTO_SUB})

find_package(boost_asio REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::asio)

find_package(boost_uuid REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::uuid)

find_package(protobuf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp)