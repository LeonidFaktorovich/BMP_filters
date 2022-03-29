#include "Crystallize.h"

#include <math.h>

#include <iostream>
#include <random>

Crystallize::Crystallize(int count) : count(count) {
}

void Crystallize::DoFilter(Image* image) {
    std::vector<std::pair<int, int>> random_pixels;
    unsigned int height = image->GetPixels()->GetImageHeight();
    unsigned int width = image->GetPixels()->GetImageWidth();
    random_pixels.reserve(height * width);
    for (int row = 0; row < static_cast<int>(height); ++row) {
        for (int col = 0; col < static_cast<int>(width); ++col) {
            random_pixels.push_back({row, col});
        }
    }
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(random_pixels), std::end(random_pixels), rng);
    std::vector<float> pixel_characteristics(4, 0);
    std::vector<std::vector<float>> values_of_pixels(count, pixel_characteristics);
    std::vector<int> closest_pixel(height * width, 0);
    for (uint32_t i = 0; i < height * width; ++i) {
        int x = i % width;
        int y = i / width;
        uint32_t min_dist = (x - random_pixels[0].second) * (x - random_pixels[0].second) +
                            (y - random_pixels[0].first) * (y - random_pixels[0].first) + 1;

        for (int j = 0; j < count; ++j) {
            uint32_t current_dist = (x - random_pixels[j].second) * (x - random_pixels[j].second) +
                                    (y - random_pixels[j].first) * (y - random_pixels[j].first);
            if (current_dist < min_dist) {
                min_dist = current_dist;
                closest_pixel[i] = j;
                ++values_of_pixels[j][0];
                values_of_pixels[j][1] += (*image->GetPixels())[y][x].Red();
                values_of_pixels[j][2] += (*image->GetPixels())[y][x].Green();
                values_of_pixels[j][3] += (*image->GetPixels())[y][x].Blue();
            }
        }
    }
    for (unsigned int row = 0; row < height; ++row) {
        for (unsigned int col = 0; col < width; ++col) {
            (*image->GetPixels())[row][col].Red() = values_of_pixels[closest_pixel[row * width + col]][1] /
                                                    values_of_pixels[closest_pixel[row * width + col]][0];
            (*image->GetPixels())[row][col].Green() = values_of_pixels[closest_pixel[row * width + col]][2] /
                                                      values_of_pixels[closest_pixel[row * width + col]][0];
            (*image->GetPixels())[row][col].Blue() = values_of_pixels[closest_pixel[row * width + col]][3] /
                                                     values_of_pixels[closest_pixel[row * width + col]][0];
        }
    }
}
