#pragma once
#include <vector>

#include "../Image/Image.h"

class Filter {
public:
    using Matrix = std::vector<std::vector<double>>;
    Filter() = default;
    virtual void DoFilter(Image* image) = 0;
    virtual ~Filter() = default;
};