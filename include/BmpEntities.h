#include <charconv>
#include <cstring>

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

inline ImageGeometry image_geo;