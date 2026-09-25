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

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        GIT_TAG glew-cmake-2.2.0
)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_MakeAvailable(glew)
unset(CMAKE_POLICY_VERSION_MINIMUM)

FetchContent_MakeAvailable(glew)

find_package(OpenGL REQUIRED)

add_executable(MojProjekat main.cpp
        buffer.cpp
        buffer.h
        h/shaders.h
        src/shaders.cpp
        h/render.h
        src/render.cpp)

target_link_libraries(MojProjekat PRIVATE glfw libglew_static OpenGL::GL)