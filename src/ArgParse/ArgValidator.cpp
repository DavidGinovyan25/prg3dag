#include "Arg.h"

#include <charconv>
#include <cstring>
#include <iostream>

bool ArgValidator::IsPath() {
    if (!fs::exists(path)) {
        std::cout << "ERROR: path doesnt exists" << std::endl;
        return false;
    }
    return true;
}

bool ArgValidator::IsFile() {
    if (!IsPath())
        return false;
    if (!fs::is_regular_file(path)) {
        std::cout << "ERROR: it isnt file" << std::endl;
        return false;
    }
    if (path.extension() == ".tsv") {
        std::cout << "Input file: " << path << std::endl;
        return true;
    }
    std::cout << "ERROR: file with not the one extension" << std::endl;
    return false;
}

bool ArgValidator::IsDirectory() {
    if (!IsPath())
        return false; 
    if (!fs::is_directory(path)) {
        std::cout << "ERROR: it isnt directory" << std::endl;
        return false;
    }
    std::cout << "Output directory: " << path << std::endl;
    return true;
}

bool ArgValidator::IsCorrectIndex(int argc, int index, char *key) {
    if (strncmp(key, "--", 2) ==0 ) 
        return true;
    if (index + 1 == argc) {
        std::cout << "ERROR:: index out of range" << std::endl;
        return false;
    }
    return true;
}

bool ArgValidator::IsNumber(const char* argv) { 
    int argument = 0;
    auto key = std::from_chars(argv, argv + strlen(argv),  argument);

    if (key.ec == std::errc::invalid_argument) {
        std::cout << "ERROR: number begin with not numeric symbol" << std::endl;
        return false;
    }
    if (key.ec == std::errc::result_out_of_range) {
        std::cout << "ERROR: number is out of range" << std::endl;
        return false;
    }
    if (*key.ptr != '\0') {
        std::cout << "ERROR: in argument record not numeric symbol" << std::endl;
        return false;
    }
    if (key.ec == std::errc()) 
        std::cout << "Argument: " << argument << std::endl;
    return true;
}

int GetNumber(const char* argv) {
    return std::strtol(argv, NULL, 10);
}

bool ArgValidator::NumberArgValidate(int argc, char *argv[], int i, char *arg) {
    if(!argument_validator.IsCorrectIndex(argc, i, argv[i])) 
        return false;
    if (!argument_validator.IsNumber(arg))
        return false;
    argument = GetNumber(arg);
    return true;
}

bool ArgValidator::PathArgValidate(int argc, char *argv[], int i, char *arg) {
    if(!argument_validator.IsCorrectIndex(argc, i, argv[i])) 
        return false;
    argument_validator.path = arg;
    if ((strncmp(argv[i], "-i", 2) == 0 || strncmp(argv[i], "--i", 3) == 0) && argument_validator.IsFile())
        return false;
    if (!argument_validator.IsDirectory())
        return false;
    argument = ArgConst::kPathFlag;     
    return true;
}