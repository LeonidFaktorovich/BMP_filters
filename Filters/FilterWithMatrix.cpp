#include "FilterWithMatrix.h"

#include <iostream>

FilterWithMatrix::FilterWithMatrix(Matrix matrix) : matrix(matrix) {
    if (matrix.size() != matrix[0].size() || matrix.size() % 2 == 0) {
        std::cerr << "Wrong matrix for filter";
        exit(1);
    }
}

void FilterWithMatrix::DoFilter(Image* image) {
    Pixels* new_pixels = new Pixels(*image->GetPixels());
    int center_index = matrix.size() / 2;
    unsigned int height = image->GetPixels()->GetImageHeight();
    unsigned int width = image->GetPixels()->GetImageWidth();
    for (unsigned int row = 0; row < height; ++row) {
        for (unsigned int col = 0; col < width; ++col) {
            for (int color = 0; color < 3; ++color) {
                float value = 0;
                for (size_t i = 0; i < matrix.size(); ++i) {
                    for (size_t j = 0; j < matrix.size(); ++j) {
                        if (matrix[i][j] == 0) {
                            continue;
                        }
                        value += (*image->GetPixels())[row - center_index + i][col - center_index + j]
                                     .GetFloatValues()[color] *
                                 matrix[i][j];
                    }
                }
                (*new_pixels)[row][col].GetFloatValues()[color] = value;
            }
        }
    }
    image->SetPixels(new_pixels);
}
