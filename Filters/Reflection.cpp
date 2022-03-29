#include "Reflection.h"

Reflection::Reflection(unsigned int width)
    : FilterWithAffineMatrix({{-1, 0}, {0, 1}}, {static_cast<int>(width) / 2, 0}) {
}
