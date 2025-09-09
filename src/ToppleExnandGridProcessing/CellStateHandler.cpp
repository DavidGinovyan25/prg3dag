#include "Expansion.h"

bool CellStateHandler::IsEdge(int index, int32_t side) {
    return index == 0 || index == side - 1;
}

bool CellStateHandler::SwitchStateForX(int y, int x) {
    for (int i = 0; i < x; ++i) {
        if (bmp_grid.pixel_grid[y][i] >= 4) {
            return true;
        }
    }
    return false;
}

bool CellStateHandler::SwitchStateForY(int y, int x) {
    for (int i = 0; i < y; ++i) {
        if (bmp_grid.pixel_grid[i][x] >= 4) {
            return true;
        }
    }
    return false;
}