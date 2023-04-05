cmake_minimum_required(VERSION 3.25)
project(1_1_Hello_Window)

include_directories(include/)
find_package(OpenGL REQUIRED)

add_subdirectory(libs/glad)
set(CMAKE_CXX_STANDARD 17)

add_executable(1_1_Hello_Window main.cpp)
target_link_libraries(1_1_Hello_Window glfw glad OpenGL::GL pthread X11 Xrandr Xi dl)