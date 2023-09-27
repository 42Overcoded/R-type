add_subdirectory(network)
add_subdirectory(graphics)
add_subdirectory(game)
add_subdirectory(ecs)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lboost_serialization")

add_executable(r-type_client client.cpp)
target_include_directories(r-type_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(r-type_client GameClientLibrary NetworkClientLibrary GraphicLibrary EcsLibrary)
