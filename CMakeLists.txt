cmake_minimum_required(VERSION 3.14)
project(untitled4)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

add_executable(MojProjekat main.cpp
        buffer.cpp
        buffer.h)
target_link_libraries(MojProjekat PRIVATE glfw OpenGL::GL)