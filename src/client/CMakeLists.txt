include(FetchContent)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Fetch and include SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(SFML)

add_subdirectory(network)
add_subdirectory(gameEngine)
add_subdirectory(ecs)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lboost_serialization -g")

add_executable(r-type_client client.cpp)
target_include_directories(r-type_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(r-type_client sfml-graphics sfml-window sfml-system)
target_link_libraries(r-type_client ComponentsLibrary NetworkClientLibrary GameEngineLibrary EcsLibrary)
