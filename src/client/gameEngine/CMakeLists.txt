add_library(
    GameEngineLibrary
    gameEngine.cpp
)

add_subdirectory(game)
add_subdirectory(graphics)

target_include_directories(
    GameEngineLibrary
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})
