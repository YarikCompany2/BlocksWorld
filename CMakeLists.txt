cmake_minimum_required(VERSION 3.12)

project(
    BlocksWorld
    DESCRIPTION "Simple app that creates and draws a world of many blocks. Made in C with OpengGL"
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendors)

add_executable(${PROJECT_NAME}
    include/app.h
    include/renderer.h

    src/main.c
    src/app.c
    src/renderer.c
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 90
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR OFF
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glad
    glfw
    stb_image
    OpenGL::GL
)
