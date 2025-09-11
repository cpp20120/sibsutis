cmake_minimum_required(VERSION 3.26)
project(
  SAOD
  LANGUAGES CXX
  VERSION 1.0.0
  DESCRIPTION "SAOD")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# nvim/vscode clangd helper
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

add_subdirectory(src)
target_include_directories(SAOD PUBLIC include)

