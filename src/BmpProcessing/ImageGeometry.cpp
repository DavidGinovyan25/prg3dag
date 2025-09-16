#include <cstdint>
#include <fstream>
#include <iostream>

#include "BmpEntities.h"

bool IsNegativeNumber(int16_t n) {
    if (n < 0)
        return true;
    return false;  
}

void ImageGeometry::ExtractExtremePoints(std::string input_file) { 
    std::ifstream color_grid_file(input_file);
    int16_t x;
    int16_t y;
    int16_t count; 
    while (color_grid_file >> x >> y >> count) {
        this->max_x = std::max(this->max_x, x);
        this->min_x = std::min(this->min_x, x);
        this->max_y = std::max(this->max_y, y);
        this->min_y = std::min(this->min_y, y);
    }
    if (IsNegativeNumber(min_x))
        shift_x = std::abs(min_x);
    if (IsNegativeNumber(min_y))
        shift_y = std::abs(min_y); 
}

void ImageGeometry::CalculateImageSize(){ 
    const int kPartOfSize = 1;
    this->len_x = kPartOfSize + max_x + shift_x;
    this->len_y = kPartOfSize + max_y + shift_y;
}