#pragma once

#include <cstdint>
#include <string>

struct ArgOwner {
    uint64_t max_iter = 0;
    uint64_t freq = 0;
    std::string input_file;
    std::string output_dir;
};