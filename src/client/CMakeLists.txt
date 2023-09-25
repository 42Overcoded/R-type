include(FetchContent)

# Fetch and include SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(SFML)

add_subdirectory(network)
add_subdirectory(graphics)
add_subdirectory(game)
add_subdirectory(ecs)

add_executable(r-type_client client.cpp)
target_include_directories(r-type_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(r-type_client GameClientLibrary NetworkClientLibrary GraphicLibrary EcsLibrary)
target_link_libraries(MySFMLExecutable PRIVATE sfml-graphics sfml-window sfml-system)
