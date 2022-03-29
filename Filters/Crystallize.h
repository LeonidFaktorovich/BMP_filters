#pragma once
#include "Filters.h"

class Crystallize : public Filter {
public:
    Crystallize(int count);
    void DoFilter(Image* image) override;

protected:
    int count = 0;
};