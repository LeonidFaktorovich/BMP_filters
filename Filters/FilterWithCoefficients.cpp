#include "FilterWithCoefficients.h"

FilterWithCoefficients::FilterWithCoefficients(double red_red, double red_green, double red_blue, double red_free,
                                               double green_red, double green_green, double green_blue,
                                               double green_free, double blue_red, double blue_green, double blue_blue,
                                               double blue_free)
    : red_red(red_red),
      red_green(red_green),
      red_blue(red_blue),
      red_free(red_free),
      green_red(green_red),
      green_green(green_green),
      green_blue(green_blue),
      green_free(green_free),
      blue_red(blue_red),
      blue_green(blue_green),
      blue_blue(blue_blue),
      blue_free(blue_free) {
}

void FilterWithCoefficients::DoFilter(Image* image) {
    auto height = image->GetPixels()->GetImageHeight();
    auto width = image->GetPixels()->GetImageWidth();
    for (unsigned int row = 0; row < height; ++row) {
        for (unsigned int col = 0; col < width; ++col) {
            auto pixel = (*image->GetPixels())[row][col];
            auto new_red = pixel.Red() * red_red + pixel.Green() * red_green + pixel.Blue() * red_blue + red_free;
            auto new_green =
                pixel.Red() * green_red + pixel.Green() * green_green + pixel.Blue() * green_blue + green_free;
            auto new_blue = pixel.Red() * blue_red + pixel.Green() * blue_green + pixel.Blue() * blue_blue + blue_free;
            pixel.Red() = new_red;
            pixel.Blue() = new_blue;
            pixel.Green() = new_green;
        }
    }
}
