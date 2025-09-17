#pragma once

#include "Arg.h"
#include "Expansion.h"

struct Application {
    bool Run(int argc, char *argv[]);
};

bool Application::Run(int argc, char *argv[]) {
    ArgParser argument_parser;
    argument_parser.argument_handler.argc = argc;
    ArgOwner owner;
    if (!argument_parser.Parse(argc, argv, owner)) {
        return false;
    } else {
        Expansion e;
        e.Iterations(owner);
        return true;
    }
}