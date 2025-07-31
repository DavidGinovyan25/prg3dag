#include <iostream>
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
#pragma pack(pop, 1)

const uint32_t PALETTE[16] = {
    0x00FFFFFF,  // 0: белый
    0x0000FF00,  // 1: зелёный
    0x00FF00FF,  // 2: фиолетовый
    0x0000FFFF,  // 3: жёлтый
    0x00000000,  // 4: чёрный
    0,0,0,0,0,0,0,0,0,0,0
};
//высота и ширина определяются как максимум из столбца в .tsv файле - это задаст сетку
void FillBMPFields(
    BITMAPFILEHEADER& file_header, 
    BITMAPINFOHEADER& info_header, 
    int32_t& Width, 
    int32_t& height    ) {

    uint32_t rowSize = ((Width + 1) / 2 + 3) & ~3;
    uint32_t ImageSize = rowSize * height;

    file_header = {
        .bfType = 0x4d42,
        .bfSize = 14 + 40 + 64 + ImageSize,
        .bfReserved1 = 0,
        .bfReserved2 = 0,
        .bfOffBits = 14 + 40 + 64
    };
    info_header = {
        .biSize = 40,
        .biWidth = Width,
        .biHeight = height,
        .biPlanes = 1,
        .biBitCount = 4,
        .biCompression = 0,
        .biSizeImage = ImageSize,
        .biXPelsPerMeter = 0,
        .biYPelsPerMeter = 0,
        .biClrUsed = 0,
        .biClrImportant = 0
    };
}

int main(int argc, char *argv[]) {
}