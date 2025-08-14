#include "Arg.h"

#include <cstring>
#include <iostream>

bool ArgParser::Parse(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (!argument_handler.InputFileShortFlag(argc, argv, i)) 
                return false;
            continue;

        } else if (strcmp(argv[i], "-o") == 0) {
            if (!argument_handler.OutputDirectoryShortFlag(argc, argv, i)) 
                return false;
            continue;

        } else if (strcmp(argv[i], "-m") == 0) {
            if (!argument_handler.MaxIterationsShortFlag(argc, argv, i)) 
                return false;            
            continue;

        } else if (strcmp(argv[i], "-f") == 0) {
            if (!argument_handler.FrequencyValueShortFlag(argc, argv, i)) 
                return false;            
            continue;

        } else if (strncmp(argv[i], "--input=", ArgConst::kLenOfInputFileKey) == 0) {
            if (!argument_handler.InputFileLongFlag(argv, i))
                return false; 
            continue;

        } else if (strncmp(argv[i], "--output=", ArgConst::kLenOfOutputDirectoryKey) == 0) {
            if (!argument_handler.OutputDirectoryLongFlag(argv, i))
                return false;             
            continue;

        } else if (strncmp(argv[i], "--max-iter=", ArgConst::kLenOfMaxIterationsKey) == 0) {
            if (!argument_handler.MaxIterationsLongFlag(argv, i))
                return false;             
            continue;

        } else if (strncmp(argv[i], "--freq=", ArgConst::kLenOfFrequancyKey) == 0) {
            if (!argument_handler.FrequencyValueLongFlag(argv, i))
                return false; 
            continue;

        } else if (argument_validator.argument != ArgConst::kInCorrectDataFlag) {
            argument_validator.argument = ArgConst::kInCorrectDataFlag;
            continue;
        } else {
            std::cout << "ERROR: unknown command \"" << argv[i] << "\"" << std::endl;
            return false;
        }
    }
    return true;
}