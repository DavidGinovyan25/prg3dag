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

const uint32_t PALETTE[16] = {
    0x00FFFFFF,  // 0: белый
    0x00FF0000,  // 1: зелёный
    0x00FF00FF,  // 2: фиолетовый
    0x0000FF00,  // 3: жёлтый
    0x00000000,  // 4: чёрный
    0,0,0,0,0,0,0,0,0,0,0
};

void FillBmpFields(
    BITMAPFILEHEADER& file_header, 
    BITMAPINFOHEADER& info_header, 
    int32_t& Width, 
    int32_t& height    ) {

    //uint32_t rowSize = ((Width + 1) / 2 + 3) & ~3;
    uint32_t ImageSize = Width * height; //fix: delete alignment from struct

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

struct ExtremePoints {
    int16_t max_x = INT16_MIN;
    int16_t max_y = INT16_MIN;
    int16_t min_x = INT16_MAX;
    int16_t min_y = INT16_MAX;
};

ExtremePoints image_extreme_points;

struct Size{
    int32_t len_x = 0;
    int32_t len_y = 0;
};

Size image_size;

void ExtractExtremePoints() {
    std::ifstream pixel_file;
    pixel_file.open("gen.tsv");
    int16_t x;
    int16_t y;
    int16_t count; 
    while (!pixel_file.eof()) {
        pixel_file >> x >> y;
        image_extreme_points.max_x = std::max(image_extreme_points.max_x, x);
        image_extreme_points.min_x = std::min(image_extreme_points.min_x, x);
        image_extreme_points.max_y = std::max(image_extreme_points.max_y, y);
        image_extreme_points.min_y = std::min(image_extreme_points.min_y, y);
        pixel_file >> count;
    }
}

void CalculateImageSize(){
    image_size = {
        .len_x = 1 + std::abs(image_extreme_points.max_x - image_extreme_points.min_x),
        .len_y = 1 + std::abs(image_extreme_points.max_y - image_extreme_points.min_y)
    };
}

void Initialisation(uint64_t **bmp_pixel_data) {
    std::ifstream pixel_file;
    pixel_file.open("gen.tsv");
    int16_t x;
    int16_t y;
    int16_t count; 
    while (!pixel_file.eof()) {
        pixel_file >> x >> y >> count; 
        bmp_pixel_data[x][y] = count;
    }
}

void SetBmpPixelColor(uint64_t **bmp_pixel_data) {//подумать про enum class
    for (int i = 0; i < image_size.len_x; i++) {    //для количества куч и кода цвета
        for (int j = 0; j < image_size.len_y; j++) {
            switch (bmp_pixel_data[i][j]) {
            case 0:
                bmp_pixel_data[i][j] = 0x00FFFFFF;
                continue;
            case 1:
                bmp_pixel_data[i][j] = 0x00FF0000;
                continue;
            case 2:
                bmp_pixel_data[i][j] = 0x00FF00FF;
                continue;
            case 3:
                bmp_pixel_data[i][j] = 0x0000FF00;
                continue;
            default:
                bmp_pixel_data[i][j] = 0x00000000;
                continue;
            }
        }
    }
}

void WriteFullToBmp(uint64_t **bmp_pixel_data) {//подумать про 1 пиксель - 4 бита
    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;
    std::ofstream bmp_file;
    bmp_file.open("x.bmp", std::ios::binary);
    //bmp_file.write(reinterpret_cast<const char*>(&file_header), sizeof(BITMAPFILEHEADER));
    //bmp_file.write(reinterpret_cast<const char*>(&info_header), sizeof(BITMAPINFOHEADER));
    //bmp_file.write(reinterpret_cast<const char*>(&PALETTE), sizeof(PALETTE));
    for (int i = image_size.len_x - 1; i >= 0 ; i++) { //ПО ШИРИНЕ
        //bmp_file.write(reinterpret_cast<const char *>(bmp_pixel_data[i]), sizeof(uint64_t) * image_size.len_y);
        //длина ширины
        int32_t temp = (info_header.biWidth / 2 + 3);
        int32_t count_byte = temp - (temp % 4);
        const char * zero = "0x00000000"; 
        for (int i = 0; i < count_byte - info_header.biWidth / 2; i++) {
            bmp_file.write(zero, sizeof(zero));
        }
    }
}
//Y - HEIGHT; X - WIGHT; 
int main(int argc, char *argv[]) {
    ExtractExtremePoints();
    CalculateImageSize();
    uint64_t **bmp_pixel_data = new uint64_t*[image_size.len_x * image_size.len_y];

    for (int i = 0; i < image_size.len_x; i++) {
        bmp_pixel_data[i] = new uint64_t[image_size.len_y];
    }
    for (int i = 0; i < image_size.len_x; i++) {
        for (int j = 0; j < image_size.len_y; j++) {
            bmp_pixel_data[i][j] = 0x00000000;
        }
    }
    Initialisation(bmp_pixel_data);
    SetBmpPixelColor(bmp_pixel_data);

    // for (int i = 0; i < image_size.len_x; i++) {
    //     for (int j = 0; j < image_size.len_y; j++) {
    //         std::cout << bmp_pixel_data[i][j] << std::endl;
    //     }
    // }
    WriteFullToBmp(bmp_pixel_data);
}


