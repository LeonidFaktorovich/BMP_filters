#include "../Image/Image.h"

#include <gtest/gtest.h>

TEST(Image_test, image_structure_test) {
    unsigned char header[54] = {66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};

    BMPStructure bmp_structure(header);
    ImageStructure* structure = &bmp_structure;
    EXPECT_EQ(structure->GetSizeInt(), 70);
    EXPECT_EQ(structure->GetWidthInt(), 2);
    EXPECT_EQ(structure->GetHeightInt(), 2);
    EXPECT_EQ(structure->GetCompressionInt(), 0);
    EXPECT_EQ(structure->GetBitsPerPixel(), 24);
    for (unsigned int i = 0; i < 54; ++i) {
        EXPECT_EQ(header[i], structure->GetStructureInBytes()[i]);
    }
}

TEST(Image_test, image_getters) {
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
    EXPECT_EQ(image.GetPixels(), pixels);
    EXPECT_EQ(image.GetFileStructure(), structure);
}

TEST(Image_test, image_setter) {
    unsigned char* header = new unsigned char[54]{66,  77, 70, 0,  0, 0, 0,  0,  0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
                                                  2,   0,  0,  0,  2, 0, 0,  0,  1, 0, 24, 0, 0, 0, 0,  0, 0, 0,
                                                  192, 0,  35, 46, 0, 0, 35, 46, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0};
    unsigned char* bytes = new unsigned char[16]{0, 0, 255, 255, 255, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0};
    unsigned char* new_bytes = new unsigned char[16]{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    auto pixels = PixelsBuilder()
                      .SetBytesForPixel(3)
                      .SetImageHeight(2)
                      .SetImageWidth(2)
                      .SetSizeOfBlock(4)
                      .SetBytes(16, bytes)
                      .Create();
    auto new_pixels = PixelsBuilder()
                          .SetBytesForPixel(3)
                          .SetImageHeight(2)
                          .SetImageWidth(2)
                          .SetSizeOfBlock(4)
                          .SetBytes(16, new_bytes)
                          .Create();
    ImageStructure* structure = new BMPStructure(header);
    Image image(structure, pixels);
    image.SetPixels(new_pixels);
    EXPECT_EQ(image.GetPixels(), new_pixels);
}
