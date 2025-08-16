#include <cstdint>
#include <fstream>

#include "BmpEntities.h"

void ImageGeometry::ExtractExtremePoints() { 
    std::ifstream color_grid_file;
    color_grid_file.open("gen.tsv");
    int16_t x;
    int16_t y;
    int16_t count; 
    while (!color_grid_file.eof()) {
        color_grid_file >> x >> y;
        this->max_x = std::max(this->max_x, x);
        this->min_x = std::min(this->min_x, x);
        this->max_y = std::max(this->max_y, y);
        this->min_y = std::min(this->min_y, y);
        color_grid_file >> count;
    }
}

void ImageGeometry::CalculateImageSize(){ 
    this->len_x = 1 + std::abs(this->max_x - this->min_x);
    this->len_y = 1 + std::abs(this->max_y - this->min_y);
}