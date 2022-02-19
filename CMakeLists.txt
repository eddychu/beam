cmake_minimum_required(VERSION 3.5)

project(beam LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glm REQUIRED)
find_package(OpenMP REQUIRED)



include_directories(${glm_INCLUDE_DIRS})

add_executable(beam 
    src/core/camera.h
    src/core/camera.cpp
    src/core/film.h
    src/core/ray.h
    src/core/renderer.h
    src/core/renderer.cpp
    src/core/transform.h
    src/core/hittable.h
    src/core/material.h
    src/core/scene.h

    src/objects/sphere.cpp

    src/materials/lambertian.h
    src/materials/metal.h
    src/main.cpp)

target_link_libraries(beam ${glm_LIBRARIES} ${OpenMP_LIBRARIES})