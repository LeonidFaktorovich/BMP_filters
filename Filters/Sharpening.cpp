#include "Sharpening.h"

Sharpening::Sharpening() : FilterWithMatrix({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}) {
}