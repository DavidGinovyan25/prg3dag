#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>

#pragma pack(push, 1)
struct BITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BITMAPINFOHEADER {
    uint32_t biSize ;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} ;
#pragma pack(pop)

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

struct ExtremePoints {
    int16_t max_x = INT16_MIN;
    int16_t max_y = INT16_MIN;
    int16_t min_x = INT16_MAX;
    int16_t min_y = INT16_MAX;
};

struct Size{
    int32_t len_x = 0;
    int32_t len_y = 0;
};

inline ExtremePoints image_extreme_points;
inline Size image_size;

void FillBmpFields(BITMAPFILEHEADER&, BITMAPINFOHEADER&, int32_t&, int32_t&);
void ExtractExtremePoints();
void CalculateImageSize();
void SetSandAtCoordinates(uint64_t **);
void SetBmpPixelColor(uint64_t **);
void WriteFullToBmp(uint64_t **);
void PrepearFrame(uint64_t **&);
bool parse(int, char *[]); 
