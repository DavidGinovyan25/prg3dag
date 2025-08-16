#include "Arg.h"
#include "BmpEntities.h"

struct Application {
    bool Run(int argc, char *argv[]) {
        argument_handler.argc = argc;
        if (!argument_parser.Parse(argc, argv)) {
            return false;
        } else {
            BmpPixelGrid bmp_grid;
            bmp_grid.image_geo.ExtractExtremePoints();
            bmp_grid.image_geo.CalculateImageSize();
            bmp_grid.PrepearBmpGrid(bmp_grid.pixel_grid);
            bmp_grid.PlaceSendPixel();
            bmp_grid.ExportToBmp();
            return true;
        }
    }
};