#include "Arg.h"

#include <iostream>

int ArgParser::GetNumber(const char* argv) {
    return std::strtoull(argv, nullptr, 10);
}

bool ArgParser::Parse(int argc, char *argv[], ArgOwner& owner) {
    const int kInCorrectDataFlag = -1;
    const int kCorrectDataFlag = 1;
    int argument = kInCorrectDataFlag;
    for (int i = 1; i < argc; ++i) {
        if (validator.IsCorrectArgument(argv[i], "-i")) {
            if (!argument_handler.InputFileShortFlag(argc, argv, i))
                return false;
            argument = kCorrectDataFlag;
            owner.input_file = argv[i + 1];

        } else if (validator.IsCorrectArgument(argv[i], "-o")) {
            if (!argument_handler.OutputDirectoryShortFlag(argc, argv, i)) 
                return false;
            argument = kCorrectDataFlag;
            owner.output_dir = argv[i + 1];

        } else if (validator.IsCorrectArgument(argv[i], "-m")) {
            if (!argument_handler.MaxIterationsShortFlag(argc, argv, i)) 
                return false;
            argument = kCorrectDataFlag;
            owner.max_iter = GetNumber(argv[i + 1]);

        } else if (validator.IsCorrectArgument(argv[i], "-f")) {
            if (!argument_handler.FrequencyValueShortFlag(argc, argv, i)) 
                return false; 
            argument = kCorrectDataFlag;
            owner.freq = GetNumber(argv[i + 1]);

        } else if (validator.IsCorrectArgument(argv[i], "--input=")) {
            if (!argument_handler.InputFileLongFlag(argv, i))
                return false;
            const int kLenOfInputFileKey = 8;
            argument = kCorrectDataFlag;
            owner.input_file = argv[i] + kLenOfInputFileKey;

        } else if (validator.IsCorrectArgument(argv[i], "--output=")) {
            if (!argument_handler.OutputDirectoryLongFlag(argv, i))
                return false;   
            const int kLenOfOutputDirectoryKey = 9;
            argument = kCorrectDataFlag;
            owner.output_dir = argv[i] + kLenOfOutputDirectoryKey;

        } else if (validator.IsCorrectArgument(argv[i], "--max-iter=")) {
            if (!argument_handler.MaxIterationsLongFlag(argv, i))
                return false;    
            const int kLenOfMaxIterationsKey = 11;
            argument = kCorrectDataFlag;
            owner.max_iter = GetNumber(argv[i] + kLenOfMaxIterationsKey);

        } else if (validator.IsCorrectArgument(argv[i], "--freq=")) {
            if (!argument_handler.FrequencyValueLongFlag(argv, i))
                return false;
            const int kLenOfFrequencyKey = 7;     
            argument = kCorrectDataFlag;
            owner.freq = GetNumber(argv[i] + kLenOfFrequencyKey);
            
        } else if (argument != kInCorrectDataFlag) {
            argument = kInCorrectDataFlag;
            continue;
        } else {
            std::cout << "ERROR: unknown command \"" << argv[i] << "\"" << std::endl;
            return false;
        }
    }
    return true;
}