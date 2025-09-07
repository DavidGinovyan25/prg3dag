add_library(TopplingLib STATIC
    Toppling.cpp
)

target_link_libraries(TopplingLib PUBLIC
    BmpProcessingLib
)