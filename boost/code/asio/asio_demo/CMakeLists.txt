cmake_minimum_required(VERSION 3.22.1)
project(asio_demo
    VERSION 0.0.1
    DESCRIPTION "Server demo coded using by asio."
    HOMEPAGE_URL "https://github.com/powerfulABC/cpp_learning/tree/main/asio/asio_demo"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)

find_package(boost_asio REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::asio)
find_package(boost_uuid REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::uuid)
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp)
