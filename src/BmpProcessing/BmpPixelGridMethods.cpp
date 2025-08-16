#include <fstream>

#include "BmpEntities.h"
#include "ColorAliases.h"

void BmpPixelGrid::PrepearBmpGrid(uint64_t **grid) { 
    grid = new uint64_t*[image_geo.len_x * image_geo.len_y];
    for (int i = 0; i < image_geo.len_y; ++i) {
        grid[i] = new uint64_t[image_geo.len_x]{};
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
}

void BmpPixelGrid::ExportToBmp() {
    BmpHeaders bmp_headers;
    bmp_headers.FillBmpHeaders(image_geo.len_x, image_geo.len_y);
    std::ofstream bmp_file("x.bmp", std::ios::binary);
    bmp_file.write(reinterpret_cast<const char*>(&bmp_headers.file_header), sizeof(bmp_headers.file_header));
    bmp_file.write(reinterpret_cast<const char*>(&bmp_headers.info_header), sizeof(bmp_headers.info_header));
    bmp_file.write(reinterpret_cast<const char*>(&PALETTE), sizeof(PALETTE));

    int bmp_row_size = ((image_geo.len_x + 1) / 2 + 3) & ~3; //Calculate 4bpp BMP row size with 4-byte alignment
    for (int y = image_geo.len_y - 1; y >= 0; --y) {
        char *rows = new char[bmp_row_size]{};
        for (int x = 0; x < image_geo.len_x; ++x) {
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
}