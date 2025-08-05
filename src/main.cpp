#include "bmp_data.h"

//Y - HEIGHT; X - WIGHT; 
int main(int argc, char *argv[]) {
    ExtractExtremePoints();
    CalculateImageSize();
    uint64_t **bmp_pixel_data;
    PrepearFrame(bmp_pixel_data);
    SetSandAtCoordinates(bmp_pixel_data);
    SetBmpPixelColor(bmp_pixel_data);
    //WriteFullToBmp(bmp_pixel_data);
}

