#include "Arg.h"

#include <charconv>
#include <cstring>
#include <iostream>

bool ArgValidator::IsCorrectArgument(const char *arg, const char *key) {
    return strncmp(arg, key, strlen(key)) == 0;
}

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
    std::cout << "ERROR: file " << path << "with not the one extension" << std::endl;
    return false;
}

bool ArgValidator::IsDirectory() {
    if (!IsPath())
        return false;
    if (!fs::is_directory(path)) {
        return false;
    }
    std::cout << "Output directory: " << path << std::endl;
    return true;
}

bool ArgValidator::IsNumber(const char* argv) { 
    int argume = 0;
    auto key = std::from_chars(argv, argv + strlen(argv),  argume);
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
        std::cout << "Argument: " << argume << std::endl;
    return true;
}

bool ArgValidator::IsCorrectIndex(int argc, int index, char *key) {
    if (strncmp(key, "--", 2) == 0) 
        return true;
    if (++index == argc) {
        std::cout << "ERROR:: index out of range" << std::endl;
        return false;
    }
    return true;
}

bool ArgValidator::NumberArgValidate(int argc, char *argv[], int i, char *arg) {
    if (!IsCorrectIndex(argc, i, argv[i])) 
        return false;
    if (!IsNumber(arg))
        return false;
    return true;
}

bool ArgValidator::FileArgValidate(int argc, char *argv[], int i, char *arg) {
    if (!IsCorrectIndex(argc, i, argv[i])) 
        return false;
    path = arg;
    if (!IsFile())
        return false;
    return true;
}

bool ArgValidator::PathArgValidate(int argc, char *argv[], int i, char *arg) {
    if (!IsCorrectIndex(argc, i, argv[i])) 
        return false;
    path = arg;
    if (!IsDirectory())
        return false;  
    return true;
}