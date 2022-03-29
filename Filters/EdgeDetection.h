#pragma once
#include "FilterWithMatrix.h"

class EdgeDetection : public FilterWithMatrix {
public:
    EdgeDetection(float threshold);
    void DoFilter(Image* image) override;

protected:
    float threshold = 0;
};