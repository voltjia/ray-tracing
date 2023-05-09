cmake_minimum_required(VERSION 3.10)

project("Ray Tracing")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_MPI "Use MPI." OFF)
if (USE_MPI)
    find_package(MPI REQUIRED)
endif()

find_package(PNG REQUIRED)

add_executable(trace
    src/main.cpp
    src/color.cpp
    src/vector3.cpp
    src/ray.cpp
    src/utils.cpp
    src/hittable.cpp
    src/hittable-list.cpp
    src/sphere.cpp
    src/camera.cpp
    src/lambertian.cpp
    src/metal.cpp
    src/dielectric.cpp
)

if (USE_MPI)
    target_include_directories(trace PRIVATE ${MPI_CXX_INCLUDE_DIRS})
    target_compile_definitions(trace PRIVATE USE_MPI)
    target_link_libraries(trace PRIVATE ${MPI_CXX_LIBRARIES})
endif()

target_link_libraries(trace PRIVATE PNG::PNG)
