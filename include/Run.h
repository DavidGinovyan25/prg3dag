#pragma once

#include "Arg.h"
#include "Expansion.h"

struct Application {
    bool Run(int argc, char *argv[]) {
        argument_handler.argc = argc;
        if (!argument_parser.Parse(argc, argv)) {
            return false;
        } else {
            Expansion e;
            e.Iterations();
            return true;
        }
    }
};