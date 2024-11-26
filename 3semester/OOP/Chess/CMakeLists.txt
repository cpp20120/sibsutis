cmake_minimum_required(VERSION 3.14)
project(Chess)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_subdirectory(src)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)