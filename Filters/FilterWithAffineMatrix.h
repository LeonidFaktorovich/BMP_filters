#pragma once
#include "Filters.h"

class FilterWithAffineMatrix : public Filter {
public:
    FilterWithAffineMatrix(Matrix matrix_coefficient, std::vector<int> coordinates_of_center);
    void DoFilter(Image* image) override;

protected:
    Matrix matrix;
    std::vector<int> coordinates_of_center;
};