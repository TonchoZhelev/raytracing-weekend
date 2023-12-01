# Set the minimum CMake version
cmake_minimum_required(VERSION 3.11)

# Your project name
project(RayTracer)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ 11 standard for the project
set(CMAKE_CXX_STANDARD 11)

# My sources
file(GLOB PROJECT_SOURCES src/*.cpp)

# Define the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
