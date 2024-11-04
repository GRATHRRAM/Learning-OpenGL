cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(spacewar VERSION 1.0)

add_compile_options(-Wall -Wextra -O2)

set(sources
    main.cpp
    shaders.cpp
    vertexbuffer.cpp
    indexbuffer.cpp
    renderer.cpp
    ./GLEW/glew.c
)

add_executable(swar ${sources})
target_link_libraries(swar PRIVATE GL GLU glfw)
