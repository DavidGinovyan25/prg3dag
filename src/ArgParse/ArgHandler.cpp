#include "Arg.h"

bool ArgHandler::InputFileShortFlag(int argc, char *argv[], int i) {
    if (!argument_validator.PathArgValidate(argc, argv, i, argv[i + 1]))
        return false;
    return true;
}

bool ArgHandler::OutputDirectoryShortFlag(int argc, char *argv[], int i) {
    if (!argument_validator.PathArgValidate(argc, argv, i, argv[i + 1]))
        return false;
    return true;
}

bool ArgHandler::MaxIterationsShortFlag(int argc, char *argv[], int i) {
    if (!argument_validator.NumberArgValidate(argc, argv, i, argv[i + 1]))
        return false;
    return true;
}

bool ArgHandler::FrequencyValueShortFlag(int argc, char *argv[], int i) {
    if (!argument_validator.NumberArgValidate(argc, argv, i, argv[i + 1]))
        return false;
    return true;
}

bool ArgHandler::InputFileLongFlag(char *argv[], int i) {
    if (!argument_validator.PathArgValidate(argc, argv, i, argv[i] + ArgConst::kLenOfInputFileKey))
        return false;
    return true;
}

bool ArgHandler::OutputDirectoryLongFlag(char *argv[], int i) {
    if (!argument_validator.PathArgValidate(argc, argv, i, argv[i] + ArgConst::kLenOfOutputDirectoryKey))
        return false;
    return true;
}

bool ArgHandler::MaxIterationsLongFlag(char *argv[], int i) {
    if (!argument_validator.NumberArgValidate(argc, argv, i, argv[i] + ArgConst::kLenOfMaxIterationsKey))
        return false;
    return true;
}

bool ArgHandler::FrequencyValueLongFlag(char *argv[], int i) {
    if (!argument_validator.NumberArgValidate(argc, argv, i, argv[i] + ArgConst::kLenOfFrequancyKey))
        return false;
    return true;
}