cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME r-type_server)
project(${PROJECT_NAME} VERSION 1.0)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.4
)

FetchContent_MakeAvailable(nlohmann_json)

# Fetch and include SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(SFML)

set(BOOST_INCLUDE_LIBRARIES asio filesystem system property_tree)
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
    ../gameEngine/GameEngine.hpp
    ../ecs/Registry.hpp
    ../ecs/ComponentsArray/SparseArray.hpp
    ../ecs/ComponentsArray/Components/Components.hpp
    ../ecs/ComponentsArray/Systems/ServerSystem.hpp
    ../network/Connection.hpp
    ../network/INetworkClient.hpp
    ../network/INetworkServer.hpp
    ../network/Packet.hpp
    ../network/PacketsQueue.hpp
    ../network/Protocol.hpp
    ../network/network_s/NetworkComponent.hpp
    ../network/network_s/NetworkSystem.hpp
    ../jsonfile/include/Comportment.hpp
    ../jsonfile/include/JsonParser.hpp
    ../jsonfile/include/MapLevel.hpp
    ../jsonfile/include/Mob.hpp
)

set(EXEC_SRC
    Server.cpp
    ../gameEngine/GameEngine.cpp
    ../ecs/ComponentsArray/Systems/SfmlSystem.cpp
    ../gameEngine/game/gameLogic/animation.cpp
    ../gameEngine/game/gameLogic/level1.cpp
    ../gameEngine/game/gameLogic/miscellaneous.cpp
    ../gameEngine/game/gameLogic/shoot.cpp
    ../gameEngine/game/gameLogic/movements.cpp
    ../gameEngine/game/gameInitialisation/initBullets.cpp
    ../gameEngine/game/gameInitialisation/initEnemy.cpp
    ../gameEngine/game/gameInitialisation/initMiscellaneous.cpp
    ../gameEngine/game/gameInitialisation/initStarship.cpp
    ../ecs/Registry.cpp
    ../ecs/ComponentsArray/Systems/ServerSystem.cpp
    ../network/network_s/NetworkSystem.cpp
    ../jsonfile/src/ComportmentParser.cpp
    ../jsonfile/src/GenerateMap.cpp
    ../jsonfile/src/JsonParser.cpp
    ../jsonfile/src/MapParser.cpp
    ../jsonfile/src/MobParser.cpp
    ../jsonfile/src/HandlingEcs.cpp
)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/game)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../network)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../network/network_s)
include_directories(${nlohmann_json_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${EXEC_SRC} ${INCLUDES})
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json Boost::asio Boost::filesystem Boost::system Boost::property_tree sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "R-Type Team")
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
include(CPack)
