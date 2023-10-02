add_library(
    GameLibrary
    game.cpp
)

target_include_directories(GameLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
