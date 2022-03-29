#include "Image.h"

Image::Image(ImageStructure *image_structure, Pixels *pixels) {
    file_structure_ = image_structure;
    pixels_ = pixels;
}

ImageStructure *Image::GetFileStructure() {
    return file_structure_;
}

Pixels *Image::GetPixels() {
    return pixels_;
}

void Image::SetPixels(Pixels *pixels) {
    delete[] pixels_->GetBytes();
    delete pixels_;
    pixels_ = pixels;
}

Image::~Image() {
    delete[] pixels_->GetBytes();
    delete pixels_;
    delete file_structure_;
}
