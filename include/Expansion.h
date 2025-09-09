#pragma once

#include "BmpEntities.h"

#include <memory>

struct ArrayHandler {
    BmpPixelGrid bmp_grid;
    ArrayHandler(BmpPixelGrid& b) : bmp_grid(b) {}
    void CleanArray(uint64_t**& grid);
    void CopyArray(uint64_t**& grid, int shift_y = 0, int shift_x = 0);

};

struct CellStateHandler {
    BmpPixelGrid bmp_grid;
    CellStateHandler(BmpPixelGrid& b) : bmp_grid(b) {}
    bool IsEdge(int index, int32_t side);
    bool SwitchStateForX(int y, int x);
    bool SwitchStateForY(int y, int x);
};

struct Toppling {
    void Topple(bool& stable, BmpPixelGrid& bmp_grid);
};

struct Expansion {
    BmpPixelGrid bmp_grid;
    Expansion(BmpPixelGrid& b) : bmp_grid(b) {}
    void LoadFirstGrid();
    void Iterations();
    void PrepearGridToExtend(BmpPixelGrid& bmp_grid);
};


