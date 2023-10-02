cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME server)
project(${PROJECT_NAME} VERSION 1.0)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(FetchContent)

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
    Server.hpp
    game/Game.hpp
    network/Network.hpp
    network/TestClassPlayer.hpp
)

set(EXEC_SRC
    Server.cpp
    game/Game.cpp
    network/Network.cpp
    network/TestClassPlayer.cpp
)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/game)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/network)

add_executable(${PROJECT_NAME} ${EXEC_SRC} ${INCLUDES})
target_link_libraries(${PROJECT_NAME} Boost::asio Boost::serialization)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
