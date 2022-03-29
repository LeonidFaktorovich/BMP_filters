#include "Help.h"
#include <iostream>

void Help() {
     std::cout << "\tApplication works with file formats: bmp\n"
                 "\tFilters supported by the application:\n"
                 "\tcrop (command: -crop width(integer value) height(integer value))\n"
                 "\tcrystallize (command: -crystal(integer value))\n"
                 "\tedge detection (command: -edge threshold(floating number))\n"
                 "\tblur (command: -blur sigma(floating number))\n"
                 "\tgrayscale (command: -gs)\n"
                 "\tnegative (command: -neg)\n"
                 "\treflection (command: -ref)\n"
                 "\trotation (command: -rot phi(integer value))\n"
                 "\tsharpening (command: -sharp)\n"
                 "\tThe application takes as the first parameter the path to the original image,\n"
                 "\tthe second parameter is the path to write a new image, then there are commands for\n"
                 "\tfilters and their parameters as shown above.\n"
                 "\tProgram launch example:\n "
                 "\t./image_processor before_filters.bmp after_filters.bmp -neg -rot 60 -edge 0.04 -crop 1000 1000" << std::endl;
}