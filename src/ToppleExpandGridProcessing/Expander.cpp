#include "Expansion.h"

#include <iostream>
#include <cstring> 

void Expansion::LoadFirstGrid(ArgOwner& owner) {
    bmp_grid.image_geo.ExtractExtremePoints(owner.input_file);
    bmp_grid.image_geo.CalculateImageSize();
    bmp_grid.PrepearBmpGrid(bmp_grid.pixel_grid);
    bmp_grid.PlaceSendPixel(owner.input_file);
}

void Expansion::PrepearGridToExtend(BmpPixelGrid& bmp_grid) {
    CellStateHandler cl(bmp_grid);
    bool expand_left = cl.SwitchStateForY(bmp_grid.image_geo.len_y, 0);
    bool expand_right = cl.SwitchStateForY(bmp_grid.image_geo.len_y, bmp_grid.image_geo.len_x - 1);
    bool expand_top = cl.SwitchStateForX(0, bmp_grid.image_geo.len_x);
    bool expand_bottom = cl.SwitchStateForX(bmp_grid.image_geo.len_y - 1, bmp_grid.image_geo.len_x);

    int new_len_x = bmp_grid.image_geo.len_x + (expand_left ? 1 : 0) + (expand_right ? 1 : 0);
    int new_len_y = bmp_grid.image_geo.len_y + (expand_top ? 1 : 0) + (expand_bottom ? 1 : 0);

    int shift_x = (expand_left ? 1 : 0);
    int shift_y = (expand_top ? 1 : 0);

    if (expand_left || expand_right || expand_top || expand_bottom) {
        uint64_t **new_grid = new uint64_t*[new_len_y];
        for (int i = 0; i < new_len_y; ++i) {
            new_grid[i] = new uint64_t[new_len_x]{};
        }
        ArrayHandler ah(bmp_grid);
        ah.CopyArray(new_grid, shift_y, shift_x);
        ah.CleanArray(bmp_grid.pixel_grid);
        bmp_grid.image_geo.len_x = new_len_x;
        bmp_grid.image_geo.len_y = new_len_y;
        bmp_grid.image_geo.shift_x += shift_x;
        bmp_grid.image_geo.shift_y += shift_y;
        bmp_grid.pixel_grid = new_grid;
    }
}

void Expansion::Iterations(ArgOwner& owner) {
    LoadFirstGrid(owner);
    uint64_t iter = 0;
    bool stable = false;
    std::cout << owner.max_iter << " " << owner.freq << std::endl;
    while (iter < owner.max_iter && !stable) {
        stable = true;
        PrepearGridToExtend(bmp_grid);
        Toppler top;
        top.Topple(stable, bmp_grid);
        ++iter;
        if (owner.freq == 0 && iter == owner.max_iter)
            bmp_grid.ExportToBmp(bmp_grid.pixel_grid, owner.output_dir + "frame" + ".bmp");
        if (owner.freq > 0 && iter % owner.freq == 0) {
            std::cout << "Saving iteration " << iter << " to BMP\n";
            bmp_grid.ExportToBmp(bmp_grid.pixel_grid, owner.output_dir + "frame_" + std::to_string(iter) + ".bmp");
        }
    }
    std::cout << "Finished after " << iter << " iterations\n";
}