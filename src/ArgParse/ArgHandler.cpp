#include "Arg.h"

bool ArgParser::InputFileShortFlag(int argc, char *argv[], int i) {
    if (!argument_handler.PathArgHandler(argc, argv, i, argv[i + 1]))
        return false;
    return true;
}

bool ArgParser::OutputDirectoryShortFlag(int argc, char *argv[], int i) {
    if (!argument_handler.PathArgHandler(argc, argv, i, argv[i + 1]))
        return false;
    return true;
}

bool ArgParser::MaxIterationsShortFlag(int argc, char *argv[], int i) {
    if (!argument_handler.NumberArgHandler(argc, argv, i, argv[i + 1]))
        return false;
    return true;
}

bool ArgParser::FrequancyValueShortFlag(int argc, char *argv[], int i) {
    if (!argument_handler.NumberArgHandler(argc, argv, i, argv[i + 1]))
        return false;
    return true;
}

bool ArgParser::InputFileLongFlag(char *argv[], int i) {
    if (!argument_handler.PathArgHandler(argc, argv, i, argv[i] + ArgConst::kLenOfInputFileKey))
        return false;
    return true;
}

bool ArgParser::OutputDirectoryLongFlag(char *argv[], int i) {
    if (!argument_handler.PathArgHandler(argc, argv, i, argv[i] + ArgConst::kLenOfOutputDirectoryKey))
        return false;
    return true;
}

bool ArgParser::MaxIterationsLongFlag(char *argv[], int i) {
    if (!argument_handler.NumberArgHandler(argc, argv, i, argv[i] + ArgConst::kLenOfMaxIterationsKey))
        return false;
    return true;
}

bool ArgParser::FrequancyValueLongFlag(char *argv[], int i) {
    if (!argument_handler.NumberArgHandler(argc, argv, i, argv[i] + ArgConst::kLenOfFrequancyKey))
        return false;
    return true;
}