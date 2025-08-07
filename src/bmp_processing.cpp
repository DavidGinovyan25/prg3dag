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

void SetSandAtCoordinates(uint64_t **bmp_pixel_data) {
    std::ifstream pixel_file;
    pixel_file.open("gen.tsv");
    int16_t x;
    int16_t y;
    int16_t count; 
    while (!pixel_file.eof()) {
        pixel_file >> x >> y >> count; 
        bmp_pixel_data[x][y] = count;
    }
    pixel_file.close();
}

void PrepearFrame(uint64_t **&bmp_pixel_data) {
    bmp_pixel_data = new uint64_t*[image_size.len_x * image_size.len_y];
    for (int i = 0; i < image_size.len_x; i++) {
        bmp_pixel_data[i] = new uint64_t[image_size.len_y];
    }
    for (int i = 0; i < image_size.len_x; i++) {
        for (int j = 0; j < image_size.len_y; j++) {
            bmp_pixel_data[i][j] = 0x00000000;
        }
    }
}

void SetBmpPixelColor(uint64_t **bmp_pixel_data) {
    for (int i = 0; i < image_size.len_x; i++) {   
        for (int j = 0; j < image_size.len_y; j++) {
            switch (bmp_pixel_data[i][j]) {
            case Index::Color::White:
                bmp_pixel_data[i][j] = Index::Color::White;
                continue;
            case Index::Color::Green:
                bmp_pixel_data[i][j] = Index::Color::Green;
                continue;
            case Index::Color::Violete:
                bmp_pixel_data[i][j] = Index::Color::Violete;
                continue;
            case Index::Color::Yellow:
                bmp_pixel_data[i][j] = Index::Color::Yellow;
                continue;
            default:
                bmp_pixel_data[i][j] = Index::Color::Black;
                continue;
            }
        }
    }
}

void WriteFullToBmp(uint64_t **bmp_pixel_data) {
    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;
    FillBmpFields(file_header, info_header, image_size.len_x, image_size.len_y);
    std::ofstream bmp_file("x.bmp", std::ios::binary);
    bmp_file.write(reinterpret_cast<const char*>(&file_header), sizeof(BITMAPFILEHEADER));
    bmp_file.write(reinterpret_cast<const char*>(&info_header), sizeof(BITMAPINFOHEADER));
    bmp_file.write(reinterpret_cast<const char*>(&PALETTE), sizeof(PALETTE));

    int bmp_row_size = ((image_size.len_x + 1) / 2 + 3) & ~3;
    for (int y = image_size.len_y - 1; y >= 0; y--) {
        char *rows = new char[bmp_row_size]{0};
        for (int x = 0; x < image_size.len_x; x++) {
            uint64_t color = bmp_pixel_data[x][y];
            int row_index = x / 2;
            if (x % 2 == 0) {
                rows[row_index] |= (color << 2); 
            } else {
                rows[row_index] |= color; 
            }
        }
        bmp_file.write(static_cast<const char*>(rows), bmp_row_size);
    }
    bmp_file.close();
}