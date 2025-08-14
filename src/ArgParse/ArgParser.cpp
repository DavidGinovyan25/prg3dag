#include "ExportedBmpData.h"
#include "BmpEntities.h"
#include "Arg.h"

bool ArgParser::Parse(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (!InputFileShortFlag(argc, argv, i)) 
                return false;
            continue;

        } else if (strcmp(argv[i], "-o") == 0) {
            if (!OutputDirectoryShortFlag(argc, argv, i)) 
                return false;
            continue;

        } else if (strcmp(argv[i], "-m") == 0) {
            if (!MaxIterationsShortFlag(argc, argv, i)) 
                return false;            
            continue;

        } else if (strcmp(argv[i], "-f") == 0) {
            if (!FrequancyValueShortFlag(argc, argv, i)) 
                return false;            
            continue;

        } else if (strncmp(argv[i], "--input=", ArgConst::kLenOfInputFileKey) == 0) {
            if (!InputFileLongFlag(argv, i))
                return false; 
            continue;

        } else if (strncmp(argv[i], "--output=", ArgConst::kLenOfOutputDirectoryKey) == 0) {
            if (!OutputDirectoryLongFlag(argv, i))
                return false;             
            continue;

        } else if (strncmp(argv[i], "--max-iter=", ArgConst::kLenOfMaxIterationsKey) == 0) {
            if (!MaxIterationsLongFlag(argv, i))
                return false;             
            continue;

        } else if (strncmp(argv[i], "--freq=", ArgConst::kLenOfFrequancyKey) == 0) {
            if (!FrequancyValueLongFlag(argv, i))
                return false; 
            continue;

        } else if (argument_handler.argument != ArgConst::kInCorrectDataFlag) {
            argument_handler.argument = ArgConst::kInCorrectDataFlag;
            continue;
        } else {
            std::cout << "ERROR: unknown command \"" << argv[i] << "\"" << std::endl;
            return false;
        }
    }
    return true;
}