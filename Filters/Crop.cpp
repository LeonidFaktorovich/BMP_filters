#include "Crop.h"

#include <cstring>

Crop::Crop(unsigned int width, unsigned int height) : width(width), height(height) {
}

void Crop::DoFilter(Image* image) {
    width = std::min(width, image->GetPixels()->GetImageWidth());
    height = std::min(height, image->GetPixels()->GetImageHeight());
    unsigned int bytes_in_row =
        (image->GetPixels()->GetBytesForPixel() * width + image->GetPixels()->GetSizeOfBlock() - 1) /
        image->GetPixels()->GetSizeOfBlock() * image->GetPixels()->GetSizeOfBlock();
    unsigned char* new_bytes = new unsigned char[bytes_in_row * height];
    auto new_pixels = PixelsBuilder()
                          .SetImageHeight(height)
                          .SetImageWidth(width)
                          .SetSizeOfBlock(image->GetPixels()->GetSizeOfBlock())
                          .SetBytesForPixel(image->GetFileStructure()->GetBitsPerPixel() / 8)
                          .SetBytes(bytes_in_row * height, new_bytes)
                          .Create();
    for (unsigned int row = 0; row < height; ++row) {
        std::memcpy((*new_pixels)[row].first_byte, (*image->GetPixels())[row].first_byte, bytes_in_row);
    }

    image->SetPixels(new_pixels);
    image->GetFileStructure()->SetHeightInt(height);
    image->GetFileStructure()->SetWidthInt(width);
    image->GetFileStructure()->SetSizeInt(bytes_in_row * height + 54);
}