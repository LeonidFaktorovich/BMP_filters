#pragma once
#include "Filters.h"

class Crop : public Filter {
public:
    Crop(unsigned int width, unsigned int height);
    void DoFilter(Image* image) override;

protected:
    unsigned int width = 0;
    unsigned int height = 0;
};