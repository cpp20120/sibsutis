cmake_minimum_required(VERSION 3.20)
project(1_lab)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE include)
add_executable(${PROJECT_NAME}  src/main.cpp)
