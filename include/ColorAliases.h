#include <cstdint>

enum ColorCode : uint32_t {
    kWhite = 0x00FFFFFF,
    kGreen = 0x0000FF00,
    kViolete = 0x00FF00FF,
    kYellow = 0x00FFFF00,
    kBlack = 0x00000000 
};

const uint32_t PALETTE[16] = {
    ColorCode::kWhite, 
    ColorCode::kGreen,  
    ColorCode::kViolete,  
    ColorCode::kYellow,  
    ColorCode::kBlack, ColorCode::kBlack, ColorCode::kBlack, ColorCode::kBlack,  
    ColorCode::kBlack, ColorCode::kBlack, ColorCode::kBlack, ColorCode::kBlack,
    ColorCode::kBlack, ColorCode::kBlack, ColorCode::kBlack, ColorCode::kBlack
};