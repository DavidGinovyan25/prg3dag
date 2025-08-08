#include <charconv>
#include <cstring>
#include <filesystem>

#include "bmp_data.h"

namespace fs = std::filesystem;

bool IsPath(fs::path path) {
    if (!fs::exists(path)) {
        std::cout << "ERROR: path doesnt exists" << std::endl;
        return false;
    }
    return true;
}

bool IsFile(fs::path path) {
    if (!IsPath(path))
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

bool IsDirectory(fs::path path) {
    if (!IsPath(path))
        return false; 
    if (!fs::is_directory(path)) {
        std::cout << "ERROR: it isnt directory" << std::endl;
        return false;
    }
    std::cout << "Output directory: " << path << std::endl;
    return true;
}

bool IsCorrectIndex(int argc, int index){
    if (index + 1 == argc) {
        std::cout << "ERROR:: index out of range" << std::endl;
        return false;
    }
    return true;
}

int GetNumber(const char* argv) {
    return std::strtol(argv, NULL, 10);
}

bool IsNumber(const char* argv) { 
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

const int kFLAG = -1;

void f(){}

bool parse(int argc, char *argv[]) {
    int argument = kFLAG;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if(!IsCorrectIndex(argc, i)) 
                return false;
            fs::path file = argv[i + 1];
            if (!IsFile(file))
                return false;
            f();
            continue;

        } else if (strcmp(argv[i], "-o") == 0) {
            if(!IsCorrectIndex(argc, i)) 
                return false;
            fs::path directory = argv[i + 1];
            if (!IsDirectory(directory))
                return false;
            f();
            continue;

        } else if (strcmp(argv[i], "-m") == 0) {
            if(!IsCorrectIndex(argc, i)) 
                return false;
            if (!IsNumber(argv[i + 1]))
                return false;
            argument = GetNumber(argv[i + 1]);
            continue;

        } else if (strcmp(argv[i], "-f") == 0) {
            if(!IsCorrectIndex(argc, i)) 
                return false;
            if (!IsNumber(argv[i + 1]))
                return false;
            argument = GetNumber(argv[i + 1]);
            continue;

        } else if (strncmp(argv[i], "--input=", 8) == 0) {
            fs::path file = argv[i] + 8;
            if (IsFile(file)) 
                return false;
            f();
            continue;

        } else if (strncmp(argv[i], "--output=", 9) == 0) {
            fs::path directory = argv[i] + 9;
            if (IsDirectory(directory)) 
                return false;
            f();
            continue;

        } else if (strncmp(argv[i], "--max-iter=", 11) == 0) {
            if (!IsNumber(argv[i + 1]) + 11)
                return false;
            argument = GetNumber(argv[i + 1] + 11);
            continue;

        } else if (strncmp(argv[i], "--freq=", 7) == 0) {
            if (!IsNumber(argv[i + 1]) + 7)
                return false;
            argument = GetNumber(argv[i + 1] + 7);
            continue;

        } else if (argument != kFLAG) {
            argument = kFLAG;
            continue;
        } else {
            return false;
        }
    }
    return true;
}
