#include "Arg.h"

bool ArgHandler::InputFileShortFlag(int argc, char *argv[], int i) {
    return validator.PathArgValidate(argc, argv, i, argv[i + 1]);
}

bool ArgHandler::OutputDirectoryShortFlag(int argc, char *argv[], int i) {
    return validator.PathArgValidate(argc, argv, i, argv[i + 1]);
}

bool ArgHandler::MaxIterationsShortFlag(int argc, char *argv[], int i) {
    return validator.NumberArgValidate(argc, argv, i, argv[i + 1]);
}

bool ArgHandler::FrequencyValueShortFlag(int argc, char *argv[], int i) {
    return validator.NumberArgValidate(argc, argv, i, argv[i + 1]);
}

bool ArgHandler::InputFileLongFlag(char *argv[], int i) {
    const int kLenOfInputFileKey = 8;
    return validator.PathArgValidate(argc, argv, i, argv[i] + kLenOfInputFileKey);
}

bool ArgHandler::OutputDirectoryLongFlag(char *argv[], int i) {
    const int kLenOfOutputDirectoryKey = 9;
    return validator.PathArgValidate(argc, argv, i, argv[i] + kLenOfOutputDirectoryKey);
}

bool ArgHandler::MaxIterationsLongFlag(char *argv[], int i) {
    const int kLenOfMaxIterationsKey = 11;
    return validator.NumberArgValidate(argc, argv, i, argv[i] + kLenOfMaxIterationsKey);
}

bool ArgHandler::FrequencyValueLongFlag(char *argv[], int i) {
    const int kLenOfFrequencyKey = 7;
    return validator.NumberArgValidate(argc, argv, i, argv[i] + kLenOfFrequencyKey);
}