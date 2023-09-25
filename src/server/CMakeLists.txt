set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(network)
add_subdirectory(game)

add_executable(r-type_server server.cpp)
target_include_directories(r-type_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(r-type_server GameServerLibrary)
target_link_libraries(r-type_server NetworkServerLibrary)