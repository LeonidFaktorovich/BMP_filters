#pragma once
#include <vector>

enum FileFormat {
    BMP, PNG, JPEG, UNKNOWN
};

class CommandLine {
public:
    struct DataOfFilter {
        char* name = nullptr;
        std::vector<char*> parameters;
    };
    CommandLine(int argc, char* argv[]);
    char* GetFileIn() const ;
    char* GetFileOut() const ;
    FileFormat GetFileInResolution() const;
    FileFormat GetFileOutResolution() const;
    std::vector<DataOfFilter> GetFilters() const;

private:
    FileFormat FormatFile(char* file_path);
    FileFormat FileExtension(char* file_path);
    char* file_in_;
    char* file_out_;
    FileFormat file_in_resolution_;
    FileFormat file_out_resolution_;
    std::vector<DataOfFilter> filters_;
};
