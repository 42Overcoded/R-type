set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project("RType" LANGUAGES CXX)
cmake_minimum_required(VERSION 3.12)

find_package(Boost REQUIRED COMPONENTS system)
find_package(SFML REQUIRED COMPONENTS graphics window system)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tests)