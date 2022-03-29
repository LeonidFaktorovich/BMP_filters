#include "GaussianBlur.h"

#include <math.h>

GaussianBlur::GaussianBlur(float sigma) : sigma(sigma) {
}

void GaussianBlur::DoFilter(Image* image) {
    Pixels* new_pixels = new Pixels(*image->GetPixels());
    int height = image->GetPixels()->GetImageHeight();
    int width = image->GetPixels()->GetImageWidth();
    const float sigma_with_pi = 2 * M_PI * sigma * sigma;
    const float two_sigma_square = 2 * sigma * sigma;
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            float red_value = 0;
            float blue_value = 0;
            float green_value = 0;
            for (int x = static_cast<int>(std::max(static_cast<float>(0), col - 3 * sigma));
                 x < static_cast<int>(std::min(static_cast<float>(width), col + 3 * sigma + 1)); ++x) {
                for (int y = static_cast<int>(std::max(static_cast<float>(0), row - 3 * sigma));
                     y < static_cast<int>(std::min(static_cast<float>(height), row + 3 * sigma + 1)); ++y) {
                    float coefficient = exp(((static_cast<float>(-(col - x) * (col - x))) +
                                             static_cast<float>(-(row - y) * (row - y))) /
                                            two_sigma_square) /
                                        sigma_with_pi;
                    red_value += (*image->GetPixels())[y][x].Red() * coefficient;
                    green_value += (*image->GetPixels())[y][x].Green() * coefficient;
                    blue_value += (*image->GetPixels())[y][x].Blue() * coefficient;
                }
            }
            (*new_pixels)[row][col].Red() = 1.001 * red_value;
            (*new_pixels)[row][col].Blue() = 1.001 * blue_value;
            (*new_pixels)[row][col].Green() = 1.001 * green_value;
        }
    }
    image->SetPixels(new_pixels);
}