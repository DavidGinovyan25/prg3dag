add_library(TopplingLib STATIC
    Toppling.cpp
    Expansion.cpp
    CellStateHandler.cpp
    ArrayHandler.cpp
)

target_link_libraries(TopplingLib PUBLIC
    BmpProcessingLib
)