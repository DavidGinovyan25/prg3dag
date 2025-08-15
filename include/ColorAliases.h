#include <cstdint>

namespace Index {
    enum Color : uint64_t {
        White = 0,
        Green = 1,
        Violete = 2,
        Yellow = 3,
        Black = 4 
    };
}

enum Color : uint32_t {
    White = 0x00FFFFFF,
    Green = 0x0000FF00,
    Violete = 0x00FF00FF,
    Yellow = 0x00FFFF00,
    Black = 0x00000000 
};

const uint32_t PALETTE[16] = {
    Color::White,  
    Color::Green,  
    Color::Violete,  
    Color::Yellow,  
    Color::Black,  
    0,0,0,0,0,0,0,0,0,0,0
};