#include "Pixels.h"

#include <cstring>
#include <vector>

Pixels::Pixels(unsigned char *bytes, uint64_t number_of_bytes, unsigned int image_height, unsigned int image_width,
               unsigned int size_of_block, unsigned int bytes_for_pixel)
    : bytes_(bytes),
      image_height_(image_height),
      image_width_(image_width),
      size_of_block_(size_of_block),
      bytes_for_pixel_(bytes_for_pixel),
      number_of_bytes_(number_of_bytes) {
}

Pixels::Pixels(const Pixels &pixels)
    : image_height_(pixels.GetImageHeight()),
      image_width_(pixels.GetImageWidth()),
      size_of_block_(pixels.GetSizeOfBlock()),
      bytes_for_pixel_(pixels.GetBytesForPixel()),
      number_of_bytes_(pixels.GetNumberOfBytes()) {
    bytes_ = new unsigned char[number_of_bytes_];
}

unsigned char *Pixels::GetBytes() {
    return bytes_;
}
void Pixels::SetBytes(unsigned char *new_bytes) {
    delete[] bytes_;
    bytes_ = new_bytes;
}
unsigned int Pixels::GetBytesForPixel() const {
    return bytes_for_pixel_;
}

unsigned int Pixels::GetImageHeight() const {
    return image_height_;
}

unsigned int Pixels::GetImageWidth() const {
    return image_width_;
}

unsigned int Pixels::GetSizeOfBlock() const {
    return size_of_block_;
}

uint64_t Pixels::GetNumberOfBytes() const {
    return number_of_bytes_;
}

Pixels *PixelsBuilder::Create() {
    Pixels *current_pixels =
        new Pixels(bytes_, number_of_bytes_, image_height_, image_width_, size_of_block_, bytes_for_pixel_);
    return current_pixels;
}

PixelsBuilder &PixelsBuilder::SetBytesForPixel(unsigned int bytes_for_pixels) {
    bytes_for_pixel_ = bytes_for_pixels;
    return *this;
}

PixelsBuilder &PixelsBuilder::SetImageHeight(unsigned int image_height) {
    image_height_ = image_height;
    return *this;
}

PixelsBuilder &PixelsBuilder::SetImageWidth(unsigned int image_width) {
    image_width_ = image_width;
    return *this;
}

PixelsBuilder &PixelsBuilder::SetSizeOfBlock(unsigned int size_of_block) {
    size_of_block_ = size_of_block;
    return *this;
}

PixelsBuilder &PixelsBuilder::SetBytes(uint64_t number_of_bytes, unsigned char *bytes) {
    bytes_ = bytes;
    number_of_bytes_ = number_of_bytes;
    return *this;
}

Pixels::PixelRow::PixelRow(unsigned int number_of_pixels, unsigned char *current_ptr, unsigned int bytes_in_pixel)
    : pixels_in_row(number_of_pixels), first_byte(current_ptr), bytes_for_pixel(bytes_in_pixel) {
}

Pixels::PixelRow Pixels::operator[](int32_t index_of_row) {
    int32_t index_in_file = image_height_ - 1 - index_of_row;
    unsigned int bytes_in_one_row =
        (bytes_for_pixel_ * image_width_ + size_of_block_ - 1) / size_of_block_ * size_of_block_;
    if (index_of_row < 0) {
        return PixelRow(image_width_, bytes_ + bytes_in_one_row * (image_height_ - 1), bytes_for_pixel_);
    } else if (index_of_row >= static_cast<int32_t>(image_height_)) {
        return PixelRow(image_width_, bytes_, bytes_for_pixel_);
    }
    return PixelRow(image_width_, bytes_ + bytes_in_one_row * index_in_file, bytes_for_pixel_);
}

Pixels::PixelRow::FloatRepresentation::FloatRepresentation(unsigned char *bytes, unsigned int number_of_bytes)
    : bytes_(bytes), number_of_bytes_(number_of_bytes) {
}

Pixels::PixelRow::FloatRepresentation::Color::Color(unsigned char *byte) : byte(byte) {
}

Pixels::PixelRow::FloatRepresentation::Color::operator float() {
    return (static_cast<float>(*byte) / 255);
}

Pixels::PixelRow::FloatRepresentation::Color &Pixels::PixelRow::FloatRepresentation::Color::operator=(
    float float_value) {
    *byte = static_cast<unsigned char>(
        std::min(std::max(float_value * 255, static_cast<float>(0)), static_cast<float>(255)));
    return *this;
}

Pixels::PixelRow::FloatRepresentation::Color &Pixels::PixelRow::FloatRepresentation::Color::operator=(
    const Color &other) {
    *byte = *other.byte;
    return *this;
}

std::vector<Pixels::PixelRow::FloatRepresentation::Color> Pixels::PixelRow::FloatRepresentation::GetFloatValues() {
    std::vector<Color> result;
    result.reserve(number_of_bytes_);
    auto current_byte = bytes_;
    for (size_t i = 0; i < number_of_bytes_; ++i) {
        result.push_back(Color(current_byte));
        ++current_byte;
    }
    return result;
}

Pixels::PixelRow::FloatRepresentation::Color Pixels::PixelRow::FloatRepresentation::Blue() {
    return Color(bytes_);
}

Pixels::PixelRow::FloatRepresentation::Color Pixels::PixelRow::FloatRepresentation::Green() {
    return Color(bytes_ + 1);
}

Pixels::PixelRow::FloatRepresentation::Color Pixels::PixelRow::FloatRepresentation::Red() {
    return Color(bytes_ + 2);
}

Pixels::PixelRow::FloatRepresentation::Color Pixels::PixelRow::FloatRepresentation::Alpha() {
    return Color(bytes_ + 3);
}

Pixels::PixelRow::FloatRepresentation Pixels::PixelRow::operator[](int32_t number_of_pixel) {

    unsigned char *current_byte = first_byte;
    if (number_of_pixel >= static_cast<int32_t>(pixels_in_row)) {
        current_byte = first_byte + bytes_for_pixel * (pixels_in_row - 1);
    } else if (number_of_pixel >= 0) {
        current_byte = first_byte + bytes_for_pixel * number_of_pixel;
    }
    return FloatRepresentation(current_byte, bytes_for_pixel);
}