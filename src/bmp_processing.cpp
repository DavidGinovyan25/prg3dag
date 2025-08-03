#include "bmp_data.h"

void FillBmpFields(
    BITMAPFILEHEADER& file_header, 
    BITMAPINFOHEADER& info_header, 
    int32_t& Width, 
    int32_t& height ) {

    uint32_t ImageSize = Width * height;

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

// void WriteFullToBmp(uint64_t **bmp_pixel_data) {//подумать про 1 пиксель - 4 бита
//     BITMAPFILEHEADER file_header;
//     BITMAPINFOHEADER info_header;
//     std::ofstream bmp_file;
//     bmp_file.open("x.bmp", std::ios::binary);
//     //bmp_file.write(reinterpret_cast<const char*>(&file_header), sizeof(BITMAPFILEHEADER));
//     //bmp_file.write(reinterpret_cast<const char*>(&info_header), sizeof(BITMAPINFOHEADER));
//     //bmp_file.write(reinterpret_cast<const char*>(&PALETTE), sizeof(PALETTE));
//     for (int i = image_size.len_x - 1; i >= 0 ; i++) { //ПО ШИРИНЕ
//         //bmp_file.write(reinterpret_cast<const char *>(bmp_pixel_data[i]), sizeof(uint64_t) * image_size.len_y);
//         //длина ширины
//         int32_t temp = (info_header.biWidth / 2 + 3);
//         int32_t count_byte = temp - (temp % 4);
//         const char * zero = "0x00000000"; 
//         for (int i = 0; i < count_byte - info_header.biWidth / 2; i++) {
//             //bmp_file.write(zero, sizeof(zero));
//         }
//     }
// }