add_library(
    ComponentsLibrary
    Components.cpp
)

target_include_directories(EcsLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})