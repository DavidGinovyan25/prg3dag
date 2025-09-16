#include "Expansion.h"

void ArrayHandler::CleanArray(uint64_t **&grid) {
    if (!grid) return;
    for (int i = 0; i < bmp_grid.image_geo.len_y; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
    grid = nullptr;
}


void ArrayHandler::CopyArray(uint64_t**& grid, int shift_y, int shift_x) {
    for (int y = 0; y < bmp_grid.image_geo.len_y; ++y) {
        for (int x = 0; x < bmp_grid.image_geo.len_x; ++x) {
            grid[y + shift_y][x + shift_x] = bmp_grid.pixel_grid[y][x];
        }
    }    
}