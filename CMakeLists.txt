cmake_minimum_required(VERSION 3.7)
project(PSO)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR src)
set(SOURCE_FILENAMES
        main.cpp
        window/Window.cpp
        lib/glad.c
        )

include(prepend)
prepend(SOURCE_FILES ${SOURCE_DIR} ${SOURCE_FILENAMES})

add_executable(PSO ${SOURCE_FILES})

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

target_include_directories(PSO PUBLIC
        lib/
        ${GLFW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        )

target_link_libraries(PSO
        ${GLFW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        )

if (NOT WIN32)
    target_link_libraries(PSO dl)
endif(NOT WIN32)
