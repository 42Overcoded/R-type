add_library(EcsLibrary
    EcsCore.cpp
    SparseArray.cpp
)

add_subdirectory(Components)
target_include_directories(EcsLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})