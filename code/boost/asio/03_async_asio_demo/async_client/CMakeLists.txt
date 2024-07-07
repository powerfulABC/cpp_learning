cmake_minimum_required(VERSION 3.22.1)

project(async_client)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp)

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp)

find_package(boost_asio REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::asio)