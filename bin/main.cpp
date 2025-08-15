#include "Arg.h"
#include "BmpEntities.h"
#include "ColorAliases.h"

int main(int argc, char *argv[]) {
    argument_handler.argc = argc;
    if (!argument_parser.Parse(argc, argv)) {
        return 1;
    }
    image_geo.ExtractExtremePoints();
    image_geo.CalculateImageSize();
    bmp_grid.PrepearBmpGrid();
    bmp_grid.PlaceSendPixel();
    bmp_grid.SetBmpPixelColor();
    bmp_grid.ExportToBmp();
}