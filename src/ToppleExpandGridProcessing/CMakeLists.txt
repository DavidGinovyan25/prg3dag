add_library(ToppleExpandGridProcessingLib STATIC
    Toppler.cpp
    Expander.cpp
    CellStateHandler.cpp
    ArrayHandler.cpp
)

target_link_libraries(ToppleExpandGridProcessingLib PUBLIC
    BmpProcessingLib
)