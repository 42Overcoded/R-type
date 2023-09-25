include(FetchContent)

set(BOOST_INCLUDE_LIBRARIES asio)
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

add_library(NetworkServerLibrary network.cpp)
target_include_directories(NetworkServerLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(NetworkServerLibrary Boost::asio)
