cmake_minimum_required(VERSION 3.25)
project(2_1_Shaders)

include_directories(include/)
find_package(OpenGL REQUIRED)

add_subdirectory(libs/glad)
set(CMAKE_CXX_STANDARD 17)

add_executable(2_1_Shaders main.cpp)
target_link_libraries(2_1_Shaders glfw glad OpenGL::GL pthread X11 Xrandr Xi dl)