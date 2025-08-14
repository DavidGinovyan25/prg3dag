#include "bmp_data.h"
#include "image.h"

void f(){}

int GetNumber(const char* argv) {
    return std::strtol(argv, NULL, 10);
}

bool ArgParser::ShortInputIndex(int argc, char *argv[], int i) {
    if(!argument_handler.IsCorrectIndex(argc, i)) 
        return false;
    fs::path file = argv[i + 1];
    if (!argument_handler.IsFile(file))
        return false;
    f();
    argument = kFILEFLAG;     
    return true;
}

bool ArgParser::ShortOutputIndex(int argc, char *argv[], int i) {
    if(!argument_handler.IsCorrectIndex(argc, i)) 
        return false;
    fs::path directory = argv[i + 1];
    if (!argument_handler.IsDirectory(directory))
        return false;
    f();
    argument = kFILEFLAG;
    return true;
}

bool ArgParser::ShortMaxIndex(int argc, char *argv[], int i) {
    if(!argument_handler.IsCorrectIndex(argc, i)) 
        return false;
    if (!argument_handler.IsNumber(argv[i + 1]))
        return false;
    argument = GetNumber(argv[i + 1]);
    f();
    return true;
}

bool ArgParser::ShortFreqIndex(int argc, char *argv[], int i) {
    if(!argument_handler.IsCorrectIndex(argc, i)) 
        return false;
    if (!argument_handler.IsNumber(argv[i + 1]))
        return false;
    argument = GetNumber(argv[i + 1]);
    f();
    return true;
}

bool ArgParser::LongInputIndex(int argc, char *argv[], int i) {
    fs::path file = argv[i] + 8;
    if (!argument_handler.IsFile(file)) 
        return false;
    f();
    argument = kFILEFLAG;
    return true;
}

bool ArgParser::LongOutputIndex(int argc, char *argv[], int i) {
    fs::path directory = argv[i] + 9;
    if (!argument_handler.IsDirectory(directory)) 
        return false;
    f();
    argument = kFILEFLAG;    
    return true;
}

bool ArgParser::LongMaxIndex(int argc, char *argv[], int i) {
    if (!argument_handler.IsNumber(argv[i] + 11))
        return false;
    argument = GetNumber(argv[i] + 11);
    f();    
    return true;
}

bool ArgParser::LongFreqIndex(int argc, char *argv[], int i) {
    if (!argument_handler.IsNumber(argv[i] + 7))
        return false;
    argument = GetNumber(argv[i] + 7);
    f();
    return true;
}