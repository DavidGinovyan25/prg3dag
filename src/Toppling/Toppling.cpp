#include "Expansion.h"

void Toppling::Topple(bool& stable, BmpPixelGrid& bmp_grid) {
    uint64_t **new_state = nullptr;
    bmp_grid.PrepearBmpGrid(new_state);
    ArrayHandler ah(bmp_grid);
    ah.CopyArray(new_state);
    for (int y = 0; y < bmp_grid.image_geo.len_y; ++y) {
        for (int x = 0; x < bmp_grid.image_geo.len_x; ++x) {
            if (bmp_grid.pixel_grid[y][x] >= 4) {
                stable = false;
                new_state[y][x] -= 4;
                if (y > 0)
                    ++new_state[y - 1][x];
                if (y < bmp_grid.image_geo.len_y - 1)
                    ++new_state[y + 1][x];
                if (x > 0)
                    ++new_state[y][x - 1];
                if (x < bmp_grid.image_geo.len_x - 1)
                    ++new_state[y][x + 1];
            }
        }
    }
    ah.CleanArray(bmp_grid.pixel_grid);
    bmp_grid.pixel_grid = new_state;
}