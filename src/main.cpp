#include "bmp_data.h"

//Y - HEIGHT; X - WIGHT; 
int main(int argc, char *argv[]) {
    ExtractExtremePoints();
    CalculateImageSize();
    uint64_t **bmp_pixel_data = new uint64_t*[image_size.len_x * image_size.len_y];

    for (int i = 0; i < image_size.len_x; i++) {
        bmp_pixel_data[i] = new uint64_t[image_size.len_y];
    }
    for (int i = 0; i < image_size.len_x; i++) {
        for (int j = 0; j < image_size.len_y; j++) {
            bmp_pixel_data[i][j] = 0x00000000;
        }
    }
    Initialisation(bmp_pixel_data);
    SetBmpPixelColor(bmp_pixel_data);
    //WriteFullToBmp(bmp_pixel_data);
}


