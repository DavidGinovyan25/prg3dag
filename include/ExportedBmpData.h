#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>

#pragma pack(push, 1)
struct BitMapFileHeader {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved1;
    uint16_t bf_reserved2;
    uint32_t bf_offBits;
};

struct BitMapInfoHeader {
    uint32_t bi_size ;
    int32_t bi_width;
    int32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    uint32_t bi_x_pels_per_meter;
    uint32_t bi_y_pels_per_meter;
    uint32_t bi_clr_used;
    uint32_t bi_clr_important;
};
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

struct BmpHeaders {
    BitMapFileHeader file_header;
    BitMapInfoHeader info_header;
    void FillBmpHeaders(int32_t& width, int32_t& height);
};

struct BmpPixelGrid {
    uint64_t **pixel_grid;
    void PrepearBmpGrid();
    void PlaceSendPixel();
    void SetBmpPixelColor();
    void ExportToBmp();
};

inline BmpHeaders bmp_headers;
inline BmpPixelGrid bmp_grid;