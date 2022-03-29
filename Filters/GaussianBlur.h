#pragma once
#include "Filters.h"

class GaussianBlur : public Filter {
public:
    GaussianBlur(float sigma);
    void DoFilter(Image* image) override;

protected:
    float sigma;
};
