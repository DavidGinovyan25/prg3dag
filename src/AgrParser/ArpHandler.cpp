#include "bmp_data.h"
#include "image.h"

bool ArgHandler::IsPath(fs::path path) {
    if (!fs::exists(path)) {
        std::cout << "ERROR: path doesnt exists" << std::endl;
        return false;
    }
    return true;
}

bool ArgHandler::IsFile(fs::path path) {
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

bool ArgHandler::IsDirectory(fs::path path) {
    if (!IsPath(path))
        return false; 
    if (!fs::is_directory(path)) {
        std::cout << "ERROR: it isnt directory" << std::endl;
        return false;
    }
    std::cout << "Output directory: " << path << std::endl;
    return true;
}

bool ArgHandler::IsCorrectIndex(int argc, int index) {
    if (index + 1 == argc) {
        std::cout << "ERROR:: index out of range" << std::endl;
        return false;
    }
    return true;
}

bool ArgHandler::IsNumber(const char* argv) { 
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