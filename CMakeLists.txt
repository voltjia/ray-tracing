cmake_minimum_required(VERSION 3.10)

project("Ray Tracing")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PNG REQUIRED)

add_executable(trace src/main.cpp src/color.cpp src/vector3.cpp src/ray.cpp)
target_link_libraries(trace PNG::PNG)
