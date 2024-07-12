cmake_minimum_required(VERSION 3.22.1)
project(asio_async_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp)
find_package(boost_asio REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::asio)