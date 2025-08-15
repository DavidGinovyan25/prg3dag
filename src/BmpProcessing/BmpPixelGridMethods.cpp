#include <fstream>

#include "ColorAliases.h"
#include "BmpEntities.h"

void BmpPixelGrid::PrepearBmpGrid() { 
    pixel_grid = new uint64_t*[image_geo.len_x * image_geo.len_y];
    for (int i = 0; i < image_geo.len_y; i++) {
        pixel_grid[i] = new uint64_t[image_geo.len_x];
    }
    for (int i = 0; i < image_geo.len_y; i++) {
        for (int j = 0; j < image_geo.len_x; j++) {
            pixel_grid[i][j] = 0x00000000;
        }
    }
}

void BmpPixelGrid::PlaceSendPixel() {
    std::ifstream color_grid_file;
    color_grid_file.open("gen.tsv");
    int16_t x;
    int16_t y;
    int16_t count; 
    while (!color_grid_file.eof()) {
        color_grid_file >> x >> y >> count; 
        pixel_grid[y][x] = count;
    }
    color_grid_file.close();
}

void BmpPixelGrid::SetBmpPixelColor() {
    for (int i = 0; i < image_geo.len_y; i++) {   
        for (int j = 0; j < image_geo.len_x; j++) {
            switch (pixel_grid[i][j]) {
            case Index::Color::White:
                pixel_grid[i][j] = Index::Color::White;
                continue;
            case Index::Color::Green:
                pixel_grid[i][j] = Index::Color::Green;
                continue;
            case Index::Color::Violete:
                pixel_grid[i][j] = Index::Color::Violete;
                continue;
            case Index::Color::Yellow:
                pixel_grid[i][j] = Index::Color::Yellow;
                continue;
            default:
                pixel_grid[i][j] = Index::Color::Black;
                continue;
            }
        }
    }
}

void BmpPixelGrid::ExportToBmp() {
    bmp_headers.FillBmpHeaders(image_geo.len_x, image_geo.len_y);
    std::ofstream bmp_file("x.bmp", std::ios::binary);
    bmp_file.write(reinterpret_cast<const char*>(&bmp_headers.file_header), sizeof(bmp_headers.file_header));
    bmp_file.write(reinterpret_cast<const char*>(&bmp_headers.info_header), sizeof(bmp_headers.info_header));
    bmp_file.write(reinterpret_cast<const char*>(&PALETTE), sizeof(PALETTE));

    int bmp_row_size = ((image_geo.len_x + 1) / 2 + 3) & ~3;
    for (int y = image_geo.len_y - 1; y >= 0; y--) {
        char *rows = new char[bmp_row_size]{0};
        for (int x = 0; x < image_geo.len_x; x++) {
            uint64_t color = pixel_grid[y][x];
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