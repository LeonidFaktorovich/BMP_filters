#include "Writer.h"

#include <fstream>
#include <iostream>

void WriteFileFromImage(char *path_to_file, Image &image) {
    try {
        std::ofstream file_out{std::string(path_to_file), std::ios::binary};
        file_out.write(reinterpret_cast<char *>(&(image.GetFileStructure()->GetStructureInBytes()[0])),
                       image.GetFileStructure()->GetStructureInBytes().size());
        file_out.write(reinterpret_cast<char *>(image.GetPixels()->GetBytes()), image.GetPixels()->GetNumberOfBytes());
    } catch (const std::exception &e) {
        std::cerr << "File write error: " << path_to_file << std::endl;
        exit(1);
    }
}
