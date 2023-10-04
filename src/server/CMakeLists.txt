cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME r-type_server)
project(${PROJECT_NAME} VERSION 1.0)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(FetchContent)

set(BOOST_INCLUDE_LIBRARIES asio serialization filesystem system property_tree)
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
    game/Game.hpp
    ../network_s/Network.hpp
    ../network_s/NetworkComponent.hpp
    ../network_s/NetworkSystem.hpp
    ../jsonfile/include/Comportment.hpp
    ../jsonfile/include/JsonParser.hpp
    ../jsonfile/include/MapLevel.hpp
    ../jsonfile/include/Mob.hpp
)

set(EXEC_SRC
    Server.cpp
    game/Game.cpp
    ../network_s/Network.cpp
    ../network_s/NetworkSystem.cpp
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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../network_s)

add_executable(${PROJECT_NAME} ${EXEC_SRC} ${INCLUDES})
target_link_libraries(${PROJECT_NAME} Boost::asio Boost::serialization Boost::filesystem Boost::system Boost::property_tree sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "R-Type Team")
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
include(CPack)
