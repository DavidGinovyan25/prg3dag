#include "bmp_data.h"
#include "image.h"

void BmpImage::FillBmpFields(int32_t& Width, int32_t& height) {
    uint32_t ImageSize = Width * height;
    file_header = {
        .bf_type = 0x4d42,
        .bf_size = 14 + 40 + 64 + ImageSize,
        .bf_reserved1 = 0,
        .bf_reserved2 = 0,
        .bf_offBits = 14 + 40 + 64
    };
    info_header = {
        .bi_size = 40,
        .bi_width = Width,
        .bi_height = height,
        .bi_planes = 1,
        .bi_bitCount = 4,
        .bi_compression = 0,
        .bi_sizeImage = ImageSize,
        .bi_xPelsPerMeter = 0,
        .bi_yPelsPerMeter = 0,
        .bi_clrUsed = 0,
        .bi_clrImportant = 0
    };
}

void ImageParametries::ExtractExtremePoints() { 
    std::ifstream pixel_file;
    pixel_file.open("gen.tsv");
    int16_t x;
    int16_t y;
    int16_t count; 
    while (!pixel_file.eof()) {
        pixel_file >> x >> y;
        image.max_x = std::max(image.max_x, x);
        image.min_x = std::min(image.min_x, x);
        image.max_y = std::max(image.max_y, y);
        image.min_y = std::min(image.min_y, y);
        pixel_file >> count;
    }
}

void ImageParametries::CalculateImageSize(){ 
    image = {
        .len_x = 1 + std::abs(image.max_x - image.min_x),
        .len_y = 1 + std::abs(image.max_y - image.min_y)
    };
}