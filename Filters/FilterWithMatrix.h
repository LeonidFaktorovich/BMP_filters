#pragma once
#include "Filters.h"

class FilterWithMatrix : public Filter {
public:
    FilterWithMatrix(Matrix matrix);
    void DoFilter(Image* image) override;

protected:
    Matrix matrix;
};