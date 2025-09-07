#pragma once

#include "BmpEntities.h"

struct Expansion {
    BmpPixelGrid bmp_grid;
    void CleanArray(uint64_t **&grid);
    void ClearGrid(uint64_t** grid);
    bool ShouldExpand(uint64_t** grid);
    void ExpandGrid(uint64_t**& grid);
    void ToppleCell(int y, int x, uint64_t** old_grid, uint64_t** new_grid, bool& stable); 
    bool IsEdge(int index, int32_t side);
    void Iterations();
    bool SwitchStateForX(int y, int x);
    bool SwitchStateForY(int y, int x);
    void CopyArray(uint64_t**& grid, int shift_y = 0, int shift_x = 0);
};
