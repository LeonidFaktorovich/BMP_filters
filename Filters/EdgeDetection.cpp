#include "EdgeDetection.h"

#include "Grayscale.h"

EdgeDetection::EdgeDetection(float threshold)
    : FilterWithMatrix({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), threshold(threshold) {
}

void EdgeDetection::DoFilter(Image* image) {
    Grayscale grayscale;
    grayscale.DoFilter(image);
    FilterWithMatrix::DoFilter(image);
    unsigned int height = image->GetPixels()->GetImageHeight();
    unsigned int width = image->GetPixels()->GetImageWidth();
    for (unsigned int row = 0; row < height; ++row) {
        for (unsigned int col = 0; col < width; ++col) {
            if ((*image->GetPixels())[row][col].Red() > threshold) {
                (*image->GetPixels())[row][col].Red() = 1;
                (*image->GetPixels())[row][col].Green() = 1;
                (*image->GetPixels())[row][col].Blue() = 1;
            } else {
                (*image->GetPixels())[row][col].Red() = 0;
                (*image->GetPixels())[row][col].Green() = 0;
                (*image->GetPixels())[row][col].Blue() = 0;
            }
        }
    }
}
