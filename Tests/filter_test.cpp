#include <gtest/gtest.h>

#include "../Filters/Crop.h"
#include "../Filters/EdgeDetection.h"
#include "../Filters/GaussianBlur.h"
#include "../Filters/Grayscale.h"
#include "../Filters/Negative.h"
#include "../Filters/Reflection.h"
#include "../Filters/Sharpening.h"

TEST(Filter_test, crop_test_1) {
    unsigned char* header = new unsigned char[54]{66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                                  2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                                  192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};
    unsigned char* bytes = new unsigned char[16]{0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    ImageStructure* structure = new BMPStructure(header);
    Image image(structure, pixels);
    Crop filter(1, 2);
    filter.DoFilter(&image);
    EXPECT_FLOAT_EQ(image.GetFileStructure()->GetHeightInt(), 2);
    EXPECT_FLOAT_EQ(image.GetFileStructure()->GetWidthInt(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Blue(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Blue(), 0);
}

TEST(Filter_test, crop_test_2) {
    unsigned char* header = new unsigned char[54]{66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                                  2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                                  192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};
    unsigned char* bytes = new unsigned char[16]{0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    ImageStructure* structure = new BMPStructure(header);
    Image image(structure, pixels);
    Crop filter(100, 100);
    filter.DoFilter(&image);
    EXPECT_FLOAT_EQ(image.GetFileStructure()->GetHeightInt(), 2);
    EXPECT_FLOAT_EQ(image.GetFileStructure()->GetWidthInt(), 2);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Blue(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Blue(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Blue(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Blue(), 1);
}

TEST(Filter_test, grayscale_test) {
    unsigned char* header = new unsigned char[54]{66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                                  2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                                  192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};
    unsigned char* bytes = new unsigned char[16]{0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    ImageStructure* structure = new BMPStructure(header);
    Image image(structure, pixels);
    Grayscale filter;
    filter.DoFilter(&image);
    ASSERT_NEAR((*image.GetPixels())[0][0].Red(), 0.114, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][0].Green(), 0.114, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][0].Blue(), 0.114, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][0].Red(), 0.299, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][0].Green(), 0.299, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][0].Blue(), 0.299, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][1].Red(), 0.587, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][1].Green(), 0.587, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][1].Blue(), 0.587, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][1].Red(), 1, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][1].Green(), 1, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][1].Blue(), 1, 0.01);
}

TEST(Filter_test, negative_test) {
    unsigned char* header = new unsigned char[54]{66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                                  2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                                  192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};
    unsigned char* bytes = new unsigned char[16]{0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    ImageStructure* structure = new BMPStructure(header);
    Image image(structure, pixels);
    Negative filter;
    filter.DoFilter(&image);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Blue(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Blue(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Blue(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Blue(), 0);
}

TEST(Filter_test, edge_detection_test) {
    unsigned char* header = new unsigned char[54]{66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                                  2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                                  192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};
    unsigned char* bytes = new unsigned char[16]{0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    ImageStructure* structure = new BMPStructure(header);
    Image image(structure, pixels);
    EdgeDetection filter(0.2);
    filter.DoFilter(&image);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Blue(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Blue(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Blue(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Blue(), 1);
}

TEST(Filter_test, sharpening_test) {
    unsigned char* header = new unsigned char[54]{66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                                  2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                                  192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};
    unsigned char* bytes = new unsigned char[16]{0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    ImageStructure* structure = new BMPStructure(header);
    Image image(structure, pixels);
    Sharpening filter;
    filter.DoFilter(&image);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Blue(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Blue(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Blue(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Blue(), 1);
}

TEST(Filter_test, reflection_test) {
    unsigned char* header = new unsigned char[54]{66,  77, 78, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                                  3,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                                  192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};
    unsigned char* bytes = new unsigned char[24]{0,   0, 255, 255, 255, 255, 0,   255, 255, 0, 0, 0,
                                                 255, 0, 0,   0,   255, 0,   255, 255, 0,   0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(3)
                      .SetSizeOfBlock(4)
                      .SetBytes(24, bytes)
                      .Create();
    ImageStructure* structure = new BMPStructure(header);
    Image image(structure, pixels);
    Reflection filter(2);
    filter.DoFilter(&image);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][0].Blue(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][1].Blue(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][2].Red(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][2].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[0][2].Blue(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][0].Blue(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Green(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][1].Blue(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][2].Red(), 1);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][2].Green(), 0);
    EXPECT_FLOAT_EQ((*image.GetPixels())[1][2].Blue(), 0);
}

TEST(Filter_test, blur_test) {
    unsigned char* header = new unsigned char[54]{66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                                  2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                                  192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};
    unsigned char* bytes = new unsigned char[16]{0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    ImageStructure* structure = new BMPStructure(header);
    Image image(structure, pixels);
    GaussianBlur filter(2);
    filter.DoFilter(&image);
    ASSERT_NEAR((*image.GetPixels())[0][0].Red(), 0.06, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][0].Green(), 0.06, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][0].Blue(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][1].Red(), 0.06, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][1].Green(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][1].Blue(), 0.06, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][0].Red(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][0].Green(), 0.06, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][0].Blue(), 0.06, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][1].Red(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][1].Green(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][1].Blue(), 0.07, 0.01);
}