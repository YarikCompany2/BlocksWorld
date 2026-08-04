cmake_minimum_required(VERSION 3.12)

project(
    BlocksWorld
    DESCRIPTION "Simple app that creates and draws a world of many blocks. Made in C with OpengGL"
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendors)

add_executable(${PROJECT_NAME}
    include/display/window.h

    include/math/promise_math.h
    include/math/matrix.h
    include/math/vector.h

    include/renderer/buffer.h
    include/renderer/renderer.h
    include/renderer/shader.h

    include/shape/shape.h
    include/shape/triangle.h

    include/tool/error_reporting.h
    
    include/app.h
    include/bw_enums.h

    src/display/window.c

    src/math/promise_math.c
    src/math/matrix.c
    src/math/vector.c

    src/renderer/buffer.c
    src/renderer/renderer.c
    src/renderer/shader.c

    src/shape/shape.c
    src/shape/triangle.c

    src/tool/error_reporting.c

    src/app.c
    src/main.c
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 99
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
