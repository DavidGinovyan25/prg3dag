#include <cstring>
#include <filesystem>
const int kInCorrectDataFlag = -1;

namespace fs = std::filesystem;

struct ArgValidator {
    fs::path path;
    int argument = kInCorrectDataFlag;
    bool IsPath();
    bool IsFile();
    bool IsDirectory();
    bool IsCorrectIndex(int argc, int index, char *key);
    bool IsNumber(const char* argv);
    bool NumberArgValidate(int argc, char *argv[], int i, char *arg);
    bool PathArgValidate(int argc, char *argv[], int i, char *arg);
    bool IsCorrectArgument(const char *arg, const char *key);
};

struct ArgHandler {
    fs::path file;  
    fs::path directory;
    int argc;
    bool InputFileShortFlag(int argc, char *argv[], int i);
    bool OutputDirectoryShortFlag(int argc, char *argv[], int i);
    bool MaxIterationsShortFlag(int argc, char *argv[], int i);
    bool FrequencyValueShortFlag(int argc, char *argv[], int i);
    bool InputFileLongFlag(char *argv[], int i);
    bool OutputDirectoryLongFlag(char *argv[], int i);
    bool MaxIterationsLongFlag(char *argv[], int i);
    bool FrequencyValueLongFlag(char *argv[], int i);
};

struct ArgParser {
    bool Parse(int argc, char *argv[]);
};

inline ArgValidator validator;
inline ArgHandler argument_handler;
inline ArgParser argument_parser;