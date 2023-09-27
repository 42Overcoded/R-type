add_subdirectory(ComponentsArray)

add_library(EcsLibrary Registry.cpp)
target_link_libraries(EcsLibrary ComponentsArray sfml-graphics sfml-window sfml-system)
target_include_directories(EcsLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(EcsLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ComponentsArray)
