add_library(ComponentsLibrary Components.cpp)

target_link_libraries(ComponentsLibrary sfml-graphics sfml-window sfml-system)
target_include_directories(ComponentsLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})