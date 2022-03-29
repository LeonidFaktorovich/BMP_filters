#pragma once
#include "ImageStructures.h"
#include "Pixels.h"

class Image {
public:
    Image(ImageStructure* image_structure, Pixels* pixels);
    ImageStructure* GetFileStructure();
    Pixels* GetPixels();
    void SetPixels(Pixels* pixels);
    ~Image();

private:
    ImageStructure* file_structure_;
    Pixels* pixels_;
};
