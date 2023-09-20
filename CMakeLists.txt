find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)

    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT)

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/bootstrap-vcpkg.sh")
    # Bootstrap vcpkg
    message(STATUS "Bootstrapping vcpkg")
    execute_process(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/bootstrap-vcpkg.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
        RESULT_VARIABLE VCPKG_BOOTSTRAP_RESULT)

    if(NOT VCPKG_BOOTSTRAP_RESULT EQUAL "0")
        message(FATAL_ERROR "vcpkg bootstrap failed with ${VCPKG_BOOTSTRAP_RESULT}")
    endif()
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg")
    message(FATAL_ERROR "vcpkg was not downloaded! Please update submodules and try again.")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg")
    # Install vcpkg
    message(STATUS "Installing vcpkg")
    execute_process(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg install boost-system sfml
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
        RESULT_VARIABLE VCPKG_INSTALL_RESULT)

    if(NOT VCPKG_INSTALL_RESULT EQUAL "0")
        message(FATAL_ERROR "vcpkg install failed with ${VCPKG_INSTALL_RESULT}")
    endif()
endif()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project("RType" LANGUAGES CXX)
cmake_minimum_required(VERSION 3.12)

find_package(Boost REQUIRED COMPONENTS system)
find_package(SFML REQUIRED COMPONENTS graphics window system)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tests)