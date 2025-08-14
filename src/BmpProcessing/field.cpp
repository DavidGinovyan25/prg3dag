#include "bmp_data.h"
#include "image.h"

void CoordinateField::PrepearFrame() { 
    bmp_pixel_data = new uint64_t*[image.len_x * image.len_y];
    for (int i = 0; i < image.len_y; i++) {
        bmp_pixel_data[i] = new uint64_t[image.len_x];
    }
    for (int i = 0; i < image.len_y; i++) {
        for (int j = 0; j < image.len_x; j++) {
            bmp_pixel_data[i][j] = 0x00000000;
        }
    }
}

void CoordinateField::SetSandAtCoordinates() {
    std::ifstream pixel_file;
    pixel_file.open("gen.tsv");
    int16_t x;
    int16_t y;
    int16_t count; 
    while (!pixel_file.eof()) {
        pixel_file >> x >> y >> count; 
        bmp_pixel_data[y][x] = count;
    }
    pixel_file.close();
}

void CoordinateField::SetBmpPixelColor() {
    for (int i = 0; i < image.len_y; i++) {   
        for (int j = 0; j < image.len_x; j++) {
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

void CoordinateField::WriteFullToBmp() {
    b.FillBmpFields(image.len_x, image.len_y);
    std::ofstream bmp_file("x.bmp", std::ios::binary);
    bmp_file.write(reinterpret_cast<const char*>(&b.file_header), sizeof(b.file_header));
    bmp_file.write(reinterpret_cast<const char*>(&b.info_header), sizeof(b.info_header));
    bmp_file.write(reinterpret_cast<const char*>(&PALETTE), sizeof(PALETTE));

    int bmp_row_size = ((image.len_x + 1) / 2 + 3) & ~3;
    for (int y = image.len_y - 1; y >= 0; y--) {
        char *rows = new char[bmp_row_size]{0};
        for (int x = 0; x < image.len_x; x++) {
            uint64_t color = bmp_pixel_data[y][x];
            int row_index = x / 2;
            if (x % 2 == 0) {
                rows[row_index] |= (color << 4); 
            } else {
                rows[row_index] |= color; 
            }
        }
        bmp_file.write(static_cast<const char*>(rows), bmp_row_size);
    }
    bmp_file.close();
}