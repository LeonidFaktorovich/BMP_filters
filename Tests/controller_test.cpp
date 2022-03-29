#include "../Controller/Controller.h"

#include <gtest/gtest.h>

#include "../Command_line/CommandLine.h"
#include "../Image/Image.h"

TEST(Controller_test, not_correct_filter_1) {
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
    char* filter_name_1 = strdup("a");
    CommandLine::DataOfFilter filter_1 = {filter_name_1, {}};
    EXPECT_DEATH({ FilterController controller(&image, std::vector<CommandLine::DataOfFilter>{filter_1}); },
                 "Filter: a is not supported");
    delete filter_name_1;
}

TEST(Controller_test, not_correct_filter_2) {
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
    char* filter_name_1 = strdup("neg");
    char* filter_name_2 = strdup("a");
    CommandLine::DataOfFilter filter_1 = {filter_name_1, {}};
    CommandLine::DataOfFilter filter_2 = {filter_name_2, {}};
    EXPECT_DEATH(
        {
            FilterController controller(&image, std::vector<CommandLine::DataOfFilter>{filter_1, filter_2});
        },
        "Filter: a is not supported");
    delete filter_name_1;
    delete filter_name_2;
}

TEST(Controller_test, not_correct_number_of_args) {
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
    char* filter_name_1 = strdup("neg");
    char* filter_name_2 = strdup("sharp");
    char* filter_2_arg_1 = strdup("1");
    CommandLine::DataOfFilter filter_1 = {filter_name_1, {}};
    CommandLine::DataOfFilter filter_2 = {filter_name_2, {filter_2_arg_1}};
    EXPECT_DEATH(
        {
            FilterController controller(&image, std::vector<CommandLine::DataOfFilter>{filter_1, filter_2});
        },
        "Filter sharpening expected 0 arguments, but was given 1");
    delete filter_name_1;
    delete filter_name_2;
    delete filter_2_arg_1;
}

TEST(Controller_test, do_filters) {
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
    char* filter_name_1 = strdup("neg");
    char* filter_name_2 = strdup("blur");
    char* filter_2_arg_1 = strdup("2");
    CommandLine::DataOfFilter filter_1 = {filter_name_1, {}};
    CommandLine::DataOfFilter filter_2 = {filter_name_2, {filter_2_arg_1}};
    FilterController controller(&image, std::vector<CommandLine::DataOfFilter>{filter_1, filter_2});
    controller.DoFilters();
    ASSERT_NEAR((*image.GetPixels())[0][0].Red(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][0].Green(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][0].Blue(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][0].Red(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][0].Green(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][0].Blue(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][1].Red(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][1].Green(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[0][1].Blue(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][1].Red(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][1].Green(), 0.07, 0.01);
    ASSERT_NEAR((*image.GetPixels())[1][1].Blue(), 0.07, 0.01);
    delete filter_name_1;
    delete filter_name_2;
    delete filter_2_arg_1;
}
