#include "FilterWithAffineMatrix.h"

#include <math.h>

#include <iostream>

FilterWithAffineMatrix::FilterWithAffineMatrix(Matrix matrix_coefficient, std::vector<int> coordinates_of_center)
    : matrix(matrix_coefficient), coordinates_of_center(coordinates_of_center) {
    if (matrix.size() != 2 || matrix[0].size() != 2 || coordinates_of_center.size() != 2) {
        std::cerr << "Not correct matrix for affine transformation" << std::endl;
        exit(1);
    }
}

void FilterWithAffineMatrix::DoFilter(Image* image) {
    float det_matrix = 1 / (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    Matrix inverse_matrix = {{matrix[1][1] / det_matrix, -matrix[0][1] / det_matrix},
                             {-matrix[1][0] / det_matrix, matrix[0][0] / det_matrix}};
    Pixels* new_pixels = new Pixels(*image->GetPixels());
    unsigned int height = image->GetPixels()->GetImageHeight();
    unsigned int width = image->GetPixels()->GetImageWidth();
    for (unsigned int row = 0; row < height; ++row) {
        for (unsigned int col = 0; col < width; ++col) {
            (*new_pixels)[row][col].Red() = 1;
            (*new_pixels)[row][col].Blue() = 1;
            (*new_pixels)[row][col].Green() = 1;
        }
    }
    for (unsigned int row = 0; row < height; ++row) {
        for (unsigned int col = 0; col < width; ++col) {
            unsigned int new_col = round(coordinates_of_center[0]) +
                                   round(inverse_matrix[0][0] * (static_cast<int>(col) - coordinates_of_center[0]) +
                                         inverse_matrix[0][1] * (static_cast<int>(row) - coordinates_of_center[1]));

            unsigned int new_row = round(coordinates_of_center[1]) +
                                   round(inverse_matrix[1][0] * (static_cast<int>(col) - coordinates_of_center[0]) +
                                         inverse_matrix[1][1] * (static_cast<int>(row) - coordinates_of_center[1]));
            if (new_row >= 0 && new_row < height && new_col >= 0 && new_col < width) {
                (*new_pixels)[row][col].Red() = (*image->GetPixels())[new_row][new_col].Red();
                (*new_pixels)[row][col].Blue() = (*image->GetPixels())[new_row][new_col].Blue();
                (*new_pixels)[row][col].Green() = (*image->GetPixels())[new_row][new_col].Green();
            }
        }
    }
    image->SetPixels(new_pixels);
}