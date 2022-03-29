#pragma once
#include "Filters.h"

class FilterWithCoefficients : public Filter {
public:
    FilterWithCoefficients(double red_red, double red_green, double red_blue, double red_free, double green_red,
                           double green_green, double green_blue, double green_free, double blue_red, double blue_green,
                           double blue_blue, double blue_free);
    void DoFilter(Image* image) override;

protected:
    double red_red = 0;
    double red_green = 0;
    double red_blue = 0;
    double red_free = 0;
    double green_red = 0;
    double green_green = 0;
    double green_blue = 0;
    double green_free = 0;
    double blue_red = 0;
    double blue_green = 0;
    double blue_blue = 0;
    double blue_free = 0;
};
