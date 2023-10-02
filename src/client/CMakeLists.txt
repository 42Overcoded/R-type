cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME client)
project(${PROJECT_NAME} VERSION 1.0)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(FetchContent)

# Fetch and include SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(SFML)

set(BOOST_INCLUDE_LIBRARIES asio serialization)
set(BOOST_ENABLE_CMAKE ON)

# Fetch and include Boost.Asio
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    FetchContent_Declare(
        Boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.83.0
    )
    FetchContent_MakeAvailable(Boost)
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    FetchContent_Declare(
        Boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.83.0
    )
    FetchContent_MakeAvailable(Boost)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(INCLUDES
    ecs/Registry.hpp
    ecs/ComponentsArray/SparseArray.hpp
    ecs/ComponentsArray/Components/Components.hpp
    ecs/ComponentsArray/Systems/System.hpp
    gameEngine/GameEngine.hpp
)

set(EXEC_SRC
    Client.cpp
    ecs/Registry.cpp
    ecs/ComponentsArray/Components/Components.cpp
    ecs/ComponentsArray/Systems/System.cpp
    gameEngine/GameEngine.cpp
    gameEngine/game/Game.cpp
    gameEngine/graphics/Graphic.cpp
)

add_executable(${PROJECT_NAME} ${EXEC_SRC} ${INCLUDES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system Boost::asio Boost::serialization)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
