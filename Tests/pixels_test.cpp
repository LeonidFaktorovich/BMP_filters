#include <gtest/gtest.h>

#include "../Image/Image.h"

// square [[blue green]
//         [red white]]

TEST(Pixels, checking_bytes_in_image) {
    unsigned char bytes[16] = {0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    ASSERT_FLOAT_EQ((*pixels)[0][0].Red(), 0);
    ASSERT_FLOAT_EQ((*pixels)[0][0].Blue(), 1);
    ASSERT_FLOAT_EQ((*pixels)[0][0].Green(), 0);
    ASSERT_FLOAT_EQ((*pixels)[0][1].Red(), 0);
    ASSERT_FLOAT_EQ((*pixels)[0][1].Blue(), 0);
    ASSERT_FLOAT_EQ((*pixels)[0][1].Green(), 1);
    ASSERT_FLOAT_EQ((*pixels)[1][0].Red(), 1);
    ASSERT_FLOAT_EQ((*pixels)[1][0].Blue(), 0);
    ASSERT_FLOAT_EQ((*pixels)[1][0].Green(), 0);
    ASSERT_FLOAT_EQ((*pixels)[1][1].Red(), 1);
    ASSERT_FLOAT_EQ((*pixels)[1][1].Blue(), 1);
    ASSERT_FLOAT_EQ((*pixels)[1][1].Green(), 1);
    delete pixels;
}

TEST(Pixels, checking_bytes_out_image) {
    unsigned char bytes[16] = {0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    ASSERT_FLOAT_EQ((*pixels)[-1][-1].Red(), 0);
    ASSERT_FLOAT_EQ((*pixels)[-1][-1].Blue(), 1);
    ASSERT_FLOAT_EQ((*pixels)[-1][-1].Green(), 0);
    ASSERT_FLOAT_EQ((*pixels)[-1][0].Red(), 0);
    ASSERT_FLOAT_EQ((*pixels)[-1][0].Blue(), 1);
    ASSERT_FLOAT_EQ((*pixels)[-1][0].Green(), 0);
    ASSERT_FLOAT_EQ((*pixels)[0][-1].Red(), 0);
    ASSERT_FLOAT_EQ((*pixels)[0][-1].Blue(), 1);
    ASSERT_FLOAT_EQ((*pixels)[0][-1].Green(), 0);

    ASSERT_FLOAT_EQ((*pixels)[-1][1].Red(), 0);
    ASSERT_FLOAT_EQ((*pixels)[-1][1].Blue(), 0);
    ASSERT_FLOAT_EQ((*pixels)[-1][1].Green(), 1);
    ASSERT_FLOAT_EQ((*pixels)[-1][2].Red(), 0);
    ASSERT_FLOAT_EQ((*pixels)[-1][2].Blue(), 0);
    ASSERT_FLOAT_EQ((*pixels)[-1][2].Green(), 1);
    ASSERT_FLOAT_EQ((*pixels)[0][2].Red(), 0);
    ASSERT_FLOAT_EQ((*pixels)[0][2].Blue(), 0);
    ASSERT_FLOAT_EQ((*pixels)[0][2].Green(), 1);

    ASSERT_FLOAT_EQ((*pixels)[1][-1].Red(), 1);
    ASSERT_FLOAT_EQ((*pixels)[1][-1].Blue(), 0);
    ASSERT_FLOAT_EQ((*pixels)[1][-1].Green(), 0);
    ASSERT_FLOAT_EQ((*pixels)[2][0].Red(), 1);
    ASSERT_FLOAT_EQ((*pixels)[2][0].Blue(), 0);
    ASSERT_FLOAT_EQ((*pixels)[2][0].Green(), 0);
    ASSERT_FLOAT_EQ((*pixels)[2][-1].Red(), 1);
    ASSERT_FLOAT_EQ((*pixels)[2][-1].Blue(), 0);
    ASSERT_FLOAT_EQ((*pixels)[2][-1].Green(), 0);

    ASSERT_FLOAT_EQ((*pixels)[1][2].Red(), 1);
    ASSERT_FLOAT_EQ((*pixels)[1][2].Blue(), 1);
    ASSERT_FLOAT_EQ((*pixels)[1][2].Green(), 1);
    ASSERT_FLOAT_EQ((*pixels)[2][1].Red(), 1);
    ASSERT_FLOAT_EQ((*pixels)[2][1].Blue(), 1);
    ASSERT_FLOAT_EQ((*pixels)[2][1].Green(), 1);
    ASSERT_FLOAT_EQ((*pixels)[2][2].Red(), 1);
    ASSERT_FLOAT_EQ((*pixels)[2][2].Blue(), 1);
    ASSERT_FLOAT_EQ((*pixels)[2][2].Green(), 1);
    delete pixels;
}

TEST(Pixels, main_parameters) {
    unsigned char bytes[16] = {0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    ASSERT_EQ(pixels->GetImageWidth(), 2);
    ASSERT_EQ(pixels->GetImageHeight(), 2);
    ASSERT_EQ(pixels->GetBytes(), bytes);
    ASSERT_EQ(pixels->GetNumberOfBytes(), 16);
    ASSERT_EQ(pixels->GetBytesForPixel(), 3);
    ASSERT_EQ(pixels->GetSizeOfBlock(), 4);
    delete pixels;
}

TEST(Pixels, pixel_row) {
    unsigned char bytes[16] = {0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    auto row_0 = (*pixels)[0];
    ASSERT_EQ(row_0.bytes_for_pixel, 3);
    ASSERT_EQ(row_0.pixels_in_row, 2);
    ASSERT_EQ(row_0.first_byte, &bytes[8]);

    auto row_1 = (*pixels)[1];
    ASSERT_EQ(row_1.bytes_for_pixel, 3);
    ASSERT_EQ(row_1.pixels_in_row, 2);
    ASSERT_EQ(row_1.first_byte, &bytes[0]);
    delete pixels;
}

TEST(Pixels, pixels_float_representation) {
    unsigned char bytes[16] = {0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    auto pixel_0_0 = (*pixels)[0][0].GetFloatValues();
    std::vector<float> expected_0_0 = {1, 0, 0};
    for (unsigned int i = 0; i < 2; ++i) {
        ASSERT_EQ(float(pixel_0_0[i]), expected_0_0[i]);
    }

    auto pixel_0_1 = (*pixels)[0][1].GetFloatValues();
    std::vector<float> expected_0_1 = {0, 1, 0};
    for (unsigned int i = 0; i < 2; ++i) {
        ASSERT_EQ(float(pixel_0_1[i]), expected_0_1[i]);
    }

    auto pixel_1_0 = (*pixels)[1][0].GetFloatValues();
    std::vector<float> expected_1_0 = {0, 0, 1};
    for (unsigned int i = 0; i < 2; ++i) {
        ASSERT_EQ(float(pixel_1_0[i]), expected_1_0[i]);
    }

    auto pixel_1_1 = (*pixels)[1][1].GetFloatValues();
    std::vector<float> expected_1_1 = {1, 1, 1};
    for (unsigned int i = 0; i < 2; ++i) {
        ASSERT_EQ(float(pixel_1_1[i]), expected_1_1[i]);
    }
    delete pixels;
}

TEST(Pixels, pixels_setters) {
    unsigned char* current_bytes = new unsigned char[16];
    for (size_t i = 0; i < 16; ++i) {
        current_bytes[i] = 1;
    }
    auto current_pixels = PixelsBuilder()
                              .SetBytesForPixel(3)
                              .SetImageHeight(2)
                              .SetImageWidth(2)
                              .SetSizeOfBlock(4)
                              .SetBytes(16, current_bytes)
                              .Create();
    unsigned char* new_bytes = new unsigned char[16];
    for (size_t i = 0; i < 16; ++i) {
        new_bytes[i] = 2 / 255;
    }
    current_pixels->SetBytes(new_bytes);
    for (unsigned int row = 0; row < 2; ++row) {
        for (unsigned int col = 0; col < 2; ++col) {
            ASSERT_EQ(float((*current_pixels)[row][col].Red()), 2 / 255);
            ASSERT_EQ(float((*current_pixels)[row][col].Blue()), 2 / 255);
            ASSERT_EQ(float((*current_pixels)[row][col].Green()), 2 / 255);
        }
    }
    delete[] current_pixels->GetBytes();
    delete current_pixels;
}
