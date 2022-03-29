#include "CommandLine.h"
#include "Help.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>

FileFormat CommandLine::FormatFile(char *file_path) {
    try {
        unsigned char buf[2] = {};
        std::ifstream file_in {std::string(file_path), std::ios::binary};
        file_in.read(reinterpret_cast<char*>(buf), 2);
        file_in.close();
        if ((buf[0] == 66 && buf[1] == 77) ||
            (buf[0] == 77 && buf[1] == 66)) {
            return FileFormat::BMP;
        } else {
            return FileFormat::UNKNOWN;
        }

    } catch (std::exception& e) {
        std::cerr << "File read error: " << file_path << std::endl;
        exit(1);
    }

}

FileFormat CommandLine::FileExtension(char *file_path) {
    char *last_dot = std::strrchr(file_path, '.');
    if (last_dot == &file_path[strlen(file_path) - 1] || last_dot == nullptr) {
        throw std::runtime_error("Please enter the correct file extension: " + std::string(file_path));
    }
    auto result = std::string(std::strrchr(file_path, '.') + 1);
    if (result == "bmp") {
        return FileFormat::BMP;
    }
    else {
        return FileFormat::UNKNOWN;
    }
}

CommandLine::CommandLine(int argc, char *argv[]) {
    if (argc == 1) {
        Help();
        std::exit(0);
    } else if (argc == 2) {
        throw std::runtime_error("Please specify the path to the file to write to");
    }
    file_in_ = argv[1];
    file_out_ = argv[2];

    file_in_resolution_ = FormatFile(argv[1]);
    file_out_resolution_ = FileExtension(argv[2]);
    CommandLine::DataOfFilter new_filter;
    for (int i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (new_filter.name == nullptr && !new_filter.parameters.empty()) {
                throw std::domain_error("Enter the name of the filter first and then its parameters");
            } else if (new_filter.name != nullptr) {

                filters_.push_back(new_filter);
                new_filter.parameters.clear();
            }
            new_filter.name = &argv[i][1];
        } else {
            new_filter.parameters.push_back(argv[i]);
        }
    }
    if (new_filter.name != nullptr) {
        filters_.push_back(new_filter);
    }
    else if (!new_filter.parameters.empty()) {
        throw std::domain_error("Enter the name of the filter first and then its parameters");
    }
}

char *CommandLine::GetFileIn() const {
    return file_in_;
}

char *CommandLine::GetFileOut() const {
    return file_out_;
}

FileFormat CommandLine::GetFileInResolution() const {
    return file_in_resolution_;
}

FileFormat CommandLine::GetFileOutResolution() const {
    return file_out_resolution_;
}

std::vector<CommandLine::DataOfFilter> CommandLine::GetFilters() const {
    return filters_;
}
