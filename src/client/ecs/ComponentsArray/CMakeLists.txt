add_library(ComponentsArrayLibrary
    SparseArray.cpp
)

add_subdirectory(Components)
add_subdirectory(Systems)
target_include_directories(EcsLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})