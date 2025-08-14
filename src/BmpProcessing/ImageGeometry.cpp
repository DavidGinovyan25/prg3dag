#include "ColorAliases.h"
#include "BmpEntities.h"

void ImageGeometry::ExtractExtremePoints() { 
    std::ifstream color_grid_file;
    color_grid_file.open("gen.tsv");
    int16_t x;
    int16_t y;
    int16_t count; 
    while (!color_grid_file.eof()) {
        color_grid_file >> x >> y;
        image_geo.max_x = std::max(image_geo.max_x, x);
        image_geo.min_x = std::min(image_geo.min_x, x);
        image_geo.max_y = std::max(image_geo.max_y, y);
        image_geo.min_y = std::min(image_geo.min_y, y);
        color_grid_file >> count;
    }
}

void ImageGeometry::CalculateImageSize(){ 
    image_geo = {
        .len_x = 1 + std::abs(image_geo.max_x - image_geo.min_x),
        .len_y = 1 + std::abs(image_geo.max_y - image_geo.min_y)
    };
}