cmake_minimum_required(VERSION 3.20)

project(Chess)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SOURCES
    "src/Application/Main.cpp"
    "src/Application/Application.h"
    "src/Application/Application.cpp"
    "src/Application/ChessPanel.cpp"
    "src/Application/EnginePanel.cpp"
    "src/Application/SettingsPanel.cpp"
    "src/Application/Resources.h"

    "src/Chess/AlgebraicMove.cpp"
    "src/Chess/BitBoard.h"
    "src/Chess/Board.h"
    "src/Chess/Board.cpp"
    "src/Chess/BoardFormat.h"
    "src/Chess/ChessException.h"
    "src/Chess/Game.h"
    "src/Chess/Game.cpp"
    "src/Chess/PseudoLegal.h"
    "src/Chess/PseudoLegal.cpp"
    "src/Chess/Move.h"

    "src/Engine/Engine.h"
    "src/Engine/Engine.cpp"
    "src/Engine/EngineException.h"
    "src/Engine/Option.h"

    "src/Graphics/Buffer.h"
    "src/Graphics/Buffer.cpp"
    "src/Graphics/DebugContext.h"
    "src/Graphics/DebugContext.cpp"
    "src/Graphics/Framebuffer.h"
    "src/Graphics/Framebuffer.cpp"
    "src/Graphics/Renderer.h"
    "src/Graphics/Renderer.cpp"
    "src/Graphics/Shader.h"
    "src/Graphics/Shader.cpp"
    "src/Graphics/SubTexture.h"
    "src/Graphics/SubTexture.cpp"
    "src/Graphics/Texture.h"
    "src/Graphics/Texture.cpp"
    "src/Graphics/VertexArray.h"
    "src/Graphics/VertexArray.cpp"

    "src/Utility/FileDialog.h"
    "src/Utility/StringParser.h"
    "src/Utility/Timer.h"

    "dependencies/imgui/imgui.cpp"
    "dependencies/imgui/imgui_demo.cpp"
    "dependencies/imgui/imgui_draw.cpp"
    "dependencies/imgui/imgui_tables.cpp"
    "dependencies/imgui/imgui_widgets.cpp"
    "dependencies/imgui/backends/imgui_impl_glfw.cpp"
    "dependencies/imgui/backends/imgui_impl_opengl3.cpp"
)

if (WIN32)
    set(SOURCES
        ${SOURCES}
        "src/Platform/Windows/WindowsEngine.h"
        "src/Platform/Windows/WindowsEngine.cpp"
        "src/Platform/Windows/WindowsFileDialog.cpp"
    )

    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
elseif (UNIX)
    set(SOURCES
        ${SOURCES}
        "src/Platform/Unix/UnixEngine.h"
        "src/Platform/Unix/UnixEngine.cpp"
        "src/Platform/Unix/UnixFileDialog.cpp"
    )

    add_executable(${PROJECT_NAME} ${SOURCES})
else()
    message(FATAL_ERROR "Unsupported platform!")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    FOLDER "THINGS/"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    "src/"
)

# ------------- TESTS -------------
add_subdirectory(tests)


# ---------- DEPENDENCIES ----------

# GLFW
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(dependencies/glfw)

# OpenGL
find_package(OpenGL REQUIRED)

# glad
add_subdirectory(dependencies/glad)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    ${OPENGL_LIBRARY}
    glad
)

set_target_properties(glfw update_mappings glad PROPERTIES FOLDER "DEPENDENCIES/")

target_include_directories(${PROJECT_NAME}
    PRIVATE
    "dependencies/stb_image/"
    "dependencies/glm/"
    "dependencies/imgui/"
)
