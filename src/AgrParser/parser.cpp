#include "bmp_data.h"
#include "image.h"

bool ArgParser::Parse(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (!ShortInputIndex(argc, argv, i)) 
                return false;
            continue;

        } else if (strcmp(argv[i], "-o") == 0) {
            if (!ShortOutputIndex(argc, argv, i)) 
                return false;
            continue;

        } else if (strcmp(argv[i], "-m") == 0) {
            if (!ShortMaxIndex(argc, argv, i)) 
                return false;            
            continue;

        } else if (strcmp(argv[i], "-f") == 0) {
            if (!ShortFreqIndex(argc, argv, i)) 
                return false;            
            continue;

        } else if (strncmp(argv[i], "--input=", 8) == 0) {
            if (!LongInputIndex(argc, argv, i))
                return false; 
            continue;

        } else if (strncmp(argv[i], "--output=", 9) == 0) {
            if (!LongOutputIndex(argc, argv, i))
                return false;             
            continue;

        } else if (strncmp(argv[i], "--max-iter=", 11) == 0) {
            if (!LongMaxIndex(argc, argv, i))
                return false;             
            continue;

        } else if (strncmp(argv[i], "--freq=", 7) == 0) {
            if (!LongFreqIndex(argc, argv, i))
                return false; 
            continue;

        } else if (argument != kINCORRECTDATAFLAG) {
            argument = kINCORRECTDATAFLAG;
            continue;
        } else {
            std::cout << "ERROR: unknown command \"" << argv[i] << "\"" << std::endl;
            return false;
        }
    }
    return true;
}