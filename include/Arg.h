#include <filesystem>

namespace ArgConst {
    const int kLenOfInputFileKey = 8;
    const int kLenOfOutputDirectoryKey = 9;
    const int kLenOfMaxIterationsKey = 11;
    const int kLenOfFrequancyKey = 7;
    const int kInCorrectDataFlag = -1;
    const int kPathFlag = 1;
}

namespace fs = std::filesystem;

struct ArgValidator {
    fs::path path;
    int argument = ArgConst::kInCorrectDataFlag;
    bool IsPath();
    bool IsFile();
    bool IsDirectory();
    bool IsCorrectIndex(int argc, int index, char *key);
    bool IsNumber(const char* argv);
    bool NumberArgHandler(int argc, char *argv[], int i, char *arg);
    bool PathArgHandler(int argc, char *argv[], int i, char *arg);
};

struct ArgParser {
    fs::path file;  
    fs::path directory;
    int argc;
    bool InputFileShortFlag(int argc, char *argv[], int i);
    bool OutputDirectoryShortFlag(int argc, char *argv[], int i);
    bool MaxIterationsShortFlag(int argc, char *argv[], int i);
    bool FrequancyValueShortFlag(int argc, char *argv[], int i);
    bool InputFileLongFlag(char *argv[], int i);
    bool OutputDirectoryLongFlag(char *argv[], int i);
    bool MaxIterationsLongFlag(char *argv[], int i);
    bool FrequancyValueLongFlag(char *argv[], int i);
    bool Parse(int argc, char *argv[]);
};

inline ArgValidator argument_handler;
inline ArgParser argument_parser;