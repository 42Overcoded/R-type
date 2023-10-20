cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME r-type_client)
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

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.4 # Remplacez par la version souhaitée
)

FetchContent_MakeAvailable(nlohmann_json)

set(BOOST_INCLUDE_LIBRARIES asio filesystem property_tree)
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
    ../ecs/Registry.hpp
    ../ecs/ComponentsArray/SparseArray.hpp
    ../ecs/ComponentsArray/Components/Components.hpp
    ../ecs/ComponentsArray/Systems/SfmlSystem.hpp
    ../gameEngine/GameEngine.hpp
    ../gameEngine/game.hpp
    ../network/Connection.hpp
    ../network/INetworkClient.hpp
    ../network/INetworkServer.hpp
    ../network/Packet.hpp
    ../network/PacketsQueue.hpp
    ../network/Protocol.hpp
    ../network/network_c/NetworkComponent.hpp
    ../network/network_c/NetworkSystem.hpp
)

set(EXEC_SRC
    Client.cpp
    ../ecs/Registry.cpp
    ../ecs/ComponentsArray/Components/Components.cpp
    ../ecs/ComponentsArray/Systems/SfmlSystem.cpp
    ../gameEngine/GameEngine.cpp
    ../network/network_c/NetworkSystem.cpp
    ../gameEngine/game/gameInitialisation/initBullets.cpp
    ../gameEngine/game/gameInitialisation/initEnemy.cpp
    ../gameEngine/game/gameInitialisation/initStarship.cpp
    ../gameEngine/game/gameInitialisation/initMiscellaneous.cpp
    ../gameEngine/game/gameLogic/animation.cpp
    ../gameEngine/game/gameLogic/level1.cpp
    ../gameEngine/game/gameLogic/shoot.cpp
    ../gameEngine/game/gameLogic/miscellaneous.cpp
    ../jsonfile/src/JsonParser.cpp
    ../jsonfile/src/ComportmentParser.cpp
    ../jsonfile/src/GenerateMap.cpp
    ../jsonfile/src/HandlingEcs.cpp
    ../jsonfile/src/MapParser.cpp
    ../jsonfile/src/MobParser.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gameEngine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gameEngine/game)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gameEngine/graphics)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ecs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ecs/ComponentsArray)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ecs/ComponentsArray/Components)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ecs/ComponentsArray/Systems)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../network)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../network/network_c)
include_directories(${nlohmann_json_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${EXEC_SRC} ${INCLUDES})
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json sfml-graphics sfml-window sfml-system Boost::asio Boost::filesystem Boost::property_tree)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "R-Type Team")
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../assets DESTINATION games/rtype/assets)
include(CPack)
