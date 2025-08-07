#include <charconv>
#include <cstring>
#include <filesystem>

#include "bmp_data.h"

namespace fs = std::filesystem;

void IsPath(fs::path path) {
    if (!fs::exists(path)) {
        std::cout << "ERROR: path doesnt exists" << std::endl;
        exit(1);
    }
}

fs::path IsFile(fs::path path) {
    IsPath(path);
    if (!fs::is_regular_file(path)) {
        std::cout << "ERROR: it isnt file" << std::endl;
        exit(1);
    }
    if (path.extension() == ".tsv") {
        std::cout << "Input file: " << path << std::endl;
        return path;
    }
    std::cout << "ERROR: file with not the one extension" << std::endl;
    exit(1);
}

fs::path IsDirectory(fs::path path) {
    IsPath(path);
    if (!fs::is_directory(path)) {
        std::cout << "ERROR: it isnt directory" << std::endl;
        exit(1);
    }
    std::cout << "Output directory: " << path << std::endl;
    return path;
}

void IsCorrectIndex(int argc, int index){
    if (index + 1 == argc) {
        std::cout << "ERROR:: index out of range" << std::endl;
        exit(1);
    }
}

int IsNumber(const char* argv) { 
    int argument = 0;
    auto key = std::from_chars(argv, argv + strlen(argv),  argument);

    if (key.ec == std::errc::invalid_argument) {
        std::cout << "ERROR: number begin with not numeric symbol" << std::endl;
        exit(1);
    }
    if (key.ec == std::errc::result_out_of_range) {
        std::cout << "ERROR: number is out of range" << std::endl;
        exit(1);
    }
    if (*key.ptr != '\0') {
        std::cout << "ERROR: in argument record not numeric symbol" << std::endl;
        exit(1);
    }
    argument = std::strtol(argv, NULL, 10);
    if (key.ec == std::errc()) 
        std::cout << "Argument: " << argument << std::endl;
    return argument;
}

const int kFLAG = -1;

bool parse(int argc, char *argv[]) {
    int argument = kFLAG;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            IsCorrectIndex(argc, i);
            fs::path file = argv[i + 1];
            IsFile(file);
            continue;

        } else if (strcmp(argv[i], "-o") == 0) {
            IsCorrectIndex(argc, i);
            fs::path directory = argv[i + 1];
            IsDirectory(directory);
            continue;

        } else if (strcmp(argv[i], "-m") == 0) {
            IsCorrectIndex(argc, i);
            argument = IsNumber(argv[i + 1]);
            std::cout << argument << std::endl;
            continue;

        } else if (strcmp(argv[i], "-f") == 0) {
            IsCorrectIndex(argc, i);
            argument = IsNumber(argv[i + 1]);
            continue;

        } else if (strncmp(argv[i], "--input=", 8) == 0) {
            fs::path file = argv[i] + 8;
            IsFile(file);
            continue;

        } else if (strncmp(argv[i], "--output=", 9) == 0) {
            fs::path directory = argv[i] + 9;
            IsDirectory(directory);
            continue;

        } else if (strncmp(argv[i], "--max-iter=", 11) == 0) {
            argument = IsNumber(argv[i + 1] + 11);
            continue;

        } else if (strncmp(argv[i], "--freq=", 7) == 0) {
            argument = IsNumber(argv[i + 1] + 7);
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
