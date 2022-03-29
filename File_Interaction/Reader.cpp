#include "Reader.h"

#include <fstream>
#include <iostream>

Image ReaderBMP(char* path_to_file) {
    try {
        unsigned char buf[54] = {};
        std::ifstream file_in{std::string(path_to_file), std::ios::binary};
        file_in.read(reinterpret_cast<char*>(buf), 54);
        ImageStructure* current_file_structure = new BMPStructure(buf);
        if (static_cast<int>(buf[14]) != 40) {
            std::cerr << "This type of bmp file is not supported" << std::endl;
            exit(1);
        }
        if (static_cast<int>(buf[28]) != 24) {
            std::cerr << "BMP files with " << static_cast<int>(buf[28]) << " bits per pixel are not supported"
                      << std::endl;
            exit(1);
        }
        if (current_file_structure->GetCompressionInt() != 0) {
            std::cerr << "Compressed files are not supported, but we are already working on it" << std::endl;
            exit(1);
        }
        unsigned char* bytes = new unsigned char[current_file_structure->GetSizeInt() - 54];
        file_in.read(reinterpret_cast<char*>(bytes), current_file_structure->GetSizeInt() - 54);
        auto pixels = PixelsBuilder()
                          .SetImageWidth(current_file_structure->GetWidthInt())
                          .SetImageHeight(current_file_structure->GetHeightInt())
                          .SetSizeOfBlock(4)
                          .SetBytesForPixel(current_file_structure->GetBitsPerPixel() / 8)
                          .SetBytes(current_file_structure->GetSizeInt() - 54, bytes)
                          .Create();
        return Image(current_file_structure, pixels);
    } catch (const std::exception& e) {
        std::cerr << "File read error: " << path_to_file << std::endl;
        exit(1);
    }
}

Image ReadImageFromFile(char* path_to_file, FileFormat file_format) {
    if (file_format == FileFormat::BMP) {
        return ReaderBMP(path_to_file);
    } else {
        std::cerr << file_format << " format is not supported, but we are already working on it" << std::endl;
        exit(1);
    }
}