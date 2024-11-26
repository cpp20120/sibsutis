set(SOURCES
    board.cpp
    chessGame.cpp
    main.cpp
    piece.cpp
    pieceTextures.cpp
    )

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-window sfml-system)
