#pragma once
#include "FilterWithAffineMatrix.h"

class Rotation : public FilterWithAffineMatrix {
public:
    Rotation(float phi, unsigned int width, unsigned int height);
};
