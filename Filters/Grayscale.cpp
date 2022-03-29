#include "Grayscale.h"

Grayscale::Grayscale()
    : FilterWithCoefficients(0.299,
                             0.587,
                             0.114,
                             0,
                             0.299,
                             0.587,
                             0.114,
                             0,
                             0.299,
                             0.587,
                             0.114,
                             0) {
}
