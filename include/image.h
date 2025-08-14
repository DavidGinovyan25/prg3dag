#include <charconv>
#include <cstring>
#include <filesystem>

struct ImageParametries{
    int16_t max_x = INT16_MIN;
    int16_t max_y = INT16_MIN;
    int16_t min_x = INT16_MAX;
    int16_t min_y = INT16_MAX;
    int32_t len_x = 0;
    int32_t len_y = 0;

    void ExtractExtremePoints();
    void CalculateImageSize();
};

struct CoordinateField {
    uint64_t **bmp_pixel_data;

    void PrepearFrame();
    void SetSandAtCoordinates();
    void SetBmpPixelColor();
    void WriteFullToBmp();
};

struct BmpImage {
    BitMapFileHeader file_header;
    BitMapInfoHeader info_header;

    void FillBmpFields(int32_t& Width, int32_t& height);
};

namespace fs = std::filesystem;

struct ArgHandler {
    bool IsPath(fs::path path);
    bool IsFile(fs::path path);
    bool IsDirectory(fs::path path);
    bool IsCorrectIndex(int argc, int index);
    bool IsNumber(const char* argv);
};

const int kINCORRECTDATAFLAG = -1;
const int kFILEFLAG = 1;

struct ArgParser {
    int argument = kINCORRECTDATAFLAG;
    fs::path file;  
    fs::path directory;

    bool ShortInputIndex(int argc, char *argv[], int i);
    bool ShortOutputIndex(int argc, char *argv[], int i);
    bool ShortMaxIndex(int argc, char *argv[], int i);
    bool ShortFreqIndex(int argc, char *argv[], int i);
    bool LongInputIndex(int argc, char *argv[], int i);
    bool LongOutputIndex(int argc, char *argv[], int i);
    bool LongMaxIndex(int argc, char *argv[], int i);
    bool LongFreqIndex(int argc, char *argv[], int i);
    bool Parse(int argc, char *argv[]);
};

inline ImageParametries image;
inline CoordinateField field;
inline BmpImage b;
inline ArgHandler argument_handler;
inline ArgParser argument_parser;