cmake_minimum_required(VERSION 3.26)
project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(MOLD_PROGRAM mold)
if(MOLD_PROGRAM)
 set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=${MOLD_PROGRAM}")
endif()
# doxygen
if(DOCS)
  add_subdirectory(docs)
endif()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
endif()

file(GLOB SOURCE_FILES *.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Wextra
          -fsanitize=address>)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(format COMMAND ${CLANG_FORMAT} -i ${SOURCE_FILES})
endif()

find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY}")
endif()
