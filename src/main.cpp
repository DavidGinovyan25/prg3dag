#include "bmp_data.h"
 
int main(int argc, char *argv[]) {
    if (parse(argc, argv) == false) {
        std::cout << "ERROR: uknown command" << std::endl;
        exit(1);
    }
    ExtractExtremePoints();
    CalculateImageSize();
    uint64_t **bmp_pixel_data;
    PrepearFrame(bmp_pixel_data);
    SetSandAtCoordinates(bmp_pixel_data);
    SetBmpPixelColor(bmp_pixel_data);
    WriteFullToBmp(bmp_pixel_data);
}

