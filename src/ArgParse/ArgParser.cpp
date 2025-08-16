#include "Arg.h"

#include <iostream>

bool ArgParser::Parse(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (validator.IsCorrectArgument(argv[i], "-i")) {
            if (!argument_handler.InputFileShortFlag(argc, argv, i)) 
                return false;
        } else if (validator.IsCorrectArgument(argv[i], "-o")) {
            if (!argument_handler.OutputDirectoryShortFlag(argc, argv, i)) 
                return false;
        } else if (validator.IsCorrectArgument(argv[i], "-m")) {
            if (!argument_handler.MaxIterationsShortFlag(argc, argv, i)) 
                return false;
        } else if (validator.IsCorrectArgument(argv[i], "-f")) {
            if (!argument_handler.FrequencyValueShortFlag(argc, argv, i)) 
                return false;            
        } else if (validator.IsCorrectArgument(argv[i], "--input=")) {
            if (!argument_handler.InputFileLongFlag(argv, i))
                return false; 
        } else if (validator.IsCorrectArgument(argv[i], "--output=")) {
            if (!argument_handler.OutputDirectoryLongFlag(argv, i))
                return false;             
        } else if (validator.IsCorrectArgument(argv[i], "--max-iter=")) {
            if (!argument_handler.MaxIterationsLongFlag(argv, i))
                return false;             
        } else if (validator.IsCorrectArgument(argv[i], "--freq=")) {
            if (!argument_handler.FrequencyValueLongFlag(argv, i))
                return false; 
        } else if (validator.argument != kInCorrectDataFlag) {
            validator.argument = kInCorrectDataFlag;
            continue;
        } else {
            std::cout << "ERROR: unknown command \"" << argv[i] << "\"" << std::endl;
            return false;
        }
    }
    return true;
}