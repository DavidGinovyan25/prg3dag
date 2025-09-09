#pragma once

#include "Arg.h"
#include "Expansion.h"

struct Application {
    bool Run(int argc, char *argv[]) {
        argument_handler.argc = argc;
        if (!argument_parser.Parse(argc, argv)) {
            return false;
        } else {
            BmpPixelGrid bmp_grid;
            Expansion e(bmp_grid);
            e.Iterations();
            return true;
        }
    }
};