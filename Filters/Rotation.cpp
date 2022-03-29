#include "Rotation.h"

#include <math.h>

Rotation::Rotation(float phi, unsigned int width, unsigned int height)
    : FilterWithAffineMatrix(
          {{cos(phi * M_PI / 180), sin(phi * M_PI / 180)}, {-sin(phi * M_PI / 180), cos(phi * M_PI / 180)}},
          {static_cast<int>(width) / 2,
           static_cast<int>(height) / 2}) {
}
