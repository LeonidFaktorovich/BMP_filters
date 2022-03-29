#include <gtest/gtest.h>
#include <stdio.h>

#include <fstream>
#include <string>

#include "../File_Interaction/Reader.h"

TEST(Reading_file, reading_right_bmp_file) {
    unsigned char header[54] = {66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};

    unsigned char bytes[16] = {0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    char *file_path = strdup("test.bmp");
    std::ofstream file_out{file_path, std::ios::binary};
    file_out.write(reinterpret_cast<char *>(header), 54);
    file_out.write(reinterpret_cast<char *>(bytes), 16);
    file_out.close();
    auto reading_file = ReadImageFromFile(file_path, FileFormat::BMP);
    auto header_of_file = reading_file.GetFileStructure();
    auto bytes_of_header = header_of_file->GetStructureInBytes();
    ASSERT_EQ(bytes_of_header.size(), 54);
    for (size_t i = 0; i < 54; ++i) {
        ASSERT_EQ(bytes_of_header[i], header[i]);
    }
    std::remove(file_path);
}

TEST(Reading_file, reading_bmp_file_another_type) {
    unsigned char header[54] = {66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 60, 0, 0, 0,
                                2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};

    unsigned char bytes[16] = {0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    char *file_path = strdup("test.bmp");
    std::ofstream file_out{file_path, std::ios::binary};
    file_out.write(reinterpret_cast<char *>(header), 54);
    file_out.write(reinterpret_cast<char *>(bytes), 16);
    file_out.close();
    EXPECT_DEATH({ auto reading_file = ReadImageFromFile(file_path, FileFormat::BMP); },
                 "This type of bmp file is not supported");
}

TEST(Reading_file, reading_bmp_file_with_another_bits_per_pixel) {
    unsigned char header[54] = {66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 32, 0, 0, 0, 0,  0, 0, 0,
                                192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};

    unsigned char bytes[16] = {0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    char *file_path = strdup("test.bmp");
    std::ofstream file_out{file_path, std::ios::binary};
    file_out.write(reinterpret_cast<char *>(header), 54);
    file_out.write(reinterpret_cast<char *>(bytes), 16);
    file_out.close();
    std::string error_output = "BMP files with 32 bits per pixel are not supported";
    EXPECT_DEATH({ auto reading_file = ReadImageFromFile(file_path, FileFormat::BMP); }, error_output);
}

TEST(Reading_file, reading_bmp_file_with_compression) {
    unsigned char header[54] = {66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 2, 0, 0,  0, 0, 0,
                                192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};

    unsigned char bytes[16] = {0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    char *file_path = strdup("test.bmp");
    std::ofstream file_out{file_path, std::ios::binary};
    file_out.write(reinterpret_cast<char *>(header), 54);
    file_out.write(reinterpret_cast<char *>(bytes), 16);
    file_out.close();
    std::string error_output = "Compressed files are not supported, but we are already working on it";
    EXPECT_DEATH({ auto reading_file = ReadImageFromFile(file_path, FileFormat::BMP); }, error_output);
}
