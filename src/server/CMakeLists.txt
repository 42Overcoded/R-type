cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME r-type_server)
project(${PROJECT_NAME} VERSION 1.0)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.4 # Remplacez par la version souhaitée
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
    Server.hpp
    gameEngine/GameEngineServer.hpp
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
    gameEngine/GameEngineServer.cpp
    gameEngine/game/gameLogic/animation.cpp
    gameEngine/game/gameLogic/level1.cpp
    gameEngine/game/gameLogic/miscellaneous.cpp
    gameEngine/game/gameLogic/shoot.cpp
    gameEngine/game/gameInitialisation/initBullets.cpp
    gameEngine/game/gameInitialisation/initEnemy.cpp
    gameEngine/game/gameInitialisation/initMiscellaneous.cpp
    gameEngine/game/gameInitialisation/initStarship.cpp
    ../ecs/Registry.cpp
    ../ecs/ComponentsArray/Components/Components.cpp
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

set(BINARIES_DESTINATION "bin")
set(JSON_DESTINATION "games/rtype")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../../LICENSE")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
SET(CPACK_GENERATOR "DEB;7Z;STGZ;TGZ;TZ;ZIP;NSIS;RPM")
set(CPACK_PROJECT_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../CPackConfig.cmake")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "R-Type Team")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "freeglut3-dev, libfreetype6-dev, libx11-dev, libxrandr-dev, libudev-dev, libgl1-mesa-dev, libflac-dev, libogg-dev, libvorbis-dev, libvorbisenc2, libvorbisfile3, libopenal-dev, libpthread-stubs0-dev, xorg-dev")
SET(CPACK_RPM_PACKAGE_NAME ${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${BINARIES_DESTINATION})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../jsonfile/json DESTINATION ${JSON_DESTINATION})
include(CPack)
