#include "bmp_data.h"
#include "image.h"
 
int main(int argc, char *argv[]) {
    if (!argument_parser.Parse(argc, argv)) {
        return 1;
    }
    image.ExtractExtremePoints();
    image.CalculateImageSize();
    field.PrepearFrame();
    field.SetSandAtCoordinates();
    field.SetBmpPixelColor();
    field.WriteFullToBmp();
}

