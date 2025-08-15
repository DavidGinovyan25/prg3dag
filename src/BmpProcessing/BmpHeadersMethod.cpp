#include <cstdint>

#include "BmpEntities.h"

void BmpHeaders::FillBmpHeaders(int32_t& width, int32_t& height) {
    uint32_t image_size = width * height;
    file_header = {
        .bf_type = 0x4d42,
        .bf_size = 14 + 40 + 64 + image_size,
        .bf_reserved1 = 0,
        .bf_reserved2 = 0,
        .bf_offBits = 14 + 40 + 64
    };
    info_header = {
        .bi_size = 40,
        .bi_width = width,
        .bi_height = height,
        .bi_planes = 1,
        .bi_bit_count = 4,
        .bi_compression = 0,
        .bi_size_image = image_size,
        .bi_x_pels_per_meter = 0,
        .bi_y_pels_per_meter = 0,
        .bi_clr_used = 0,
        .bi_clr_important = 0
    };
}