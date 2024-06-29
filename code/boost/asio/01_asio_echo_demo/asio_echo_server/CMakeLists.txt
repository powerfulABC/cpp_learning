cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 指定项目名字和版本
project(asio_echo_server VERSION 0.0.1)

add_executable(${PROJECT_NAME} main.cpp)

find_package(boost_asio REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::asio)

find_package(boost_uuid REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::uuid)

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp) 