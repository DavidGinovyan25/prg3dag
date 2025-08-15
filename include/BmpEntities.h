#include <cstdint>

#pragma pack(push, 1)
struct BitMapFileHeader {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved1;
    uint16_t bf_reserved2;
    uint32_t bf_offBits;
};

struct BitMapInfoHeader {
    uint32_t bi_size ;
    int32_t bi_width;
    int32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    uint32_t bi_x_pels_per_meter;
    uint32_t bi_y_pels_per_meter;
    uint32_t bi_clr_used;
    uint32_t bi_clr_important;
};
#pragma pack(pop)

struct ImageGeometry {
    int16_t max_x = INT16_MIN;
    int16_t max_y = INT16_MIN;
    int16_t min_x = INT16_MAX;
    int16_t min_y = INT16_MAX;
    int32_t len_x = 0;
    int32_t len_y = 0;
    void ExtractExtremePoints();
    void CalculateImageSize();
};

struct BmpHeaders {
    BitMapFileHeader file_header;
    BitMapInfoHeader info_header;
    void FillBmpHeaders(int32_t& width, int32_t& height);
};

struct BmpPixelGrid {
    uint64_t **pixel_grid;
    uint64_t **temp_grid;
    void PrepearBmpGrid(uint64_t **grid);
    void PlaceSendPixel();
    void SetBmpPixelColor();
    void ExportToBmp();
};

inline ImageGeometry image_geo;
inline BmpHeaders bmp_headers;
inline BmpPixelGrid bmp_grid;