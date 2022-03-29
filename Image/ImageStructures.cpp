#include "ImageStructures.h"

#include <cstring>
#include <vector>

unsigned int ImageStructure::GetCompressionInt() const {
    return compression_type_;
}

uint64_t ImageStructure::GetSizeInt() const {
    return size_in_bytes_int_format_;
}

unsigned int ImageStructure::GetWidthInt() const {
    return image_width_int_format_;
}

unsigned int ImageStructure::GetHeightInt() const {
    return image_height_int_format_;
}

unsigned int ImageStructure::GetBitsPerPixel() const {
    return bits_per_pixel_;
}

uint64_t BytesToUINT(unsigned char *bytes, unsigned int number_of_bytes) {
    unsigned int degree = 0;
    uint64_t result = 0;
    unsigned char *current_ptr = bytes;
    for (unsigned int i = 0; i < number_of_bytes; ++i) {
        result += *current_ptr * (1 << degree);
        ++current_ptr;
        degree += 8;
    }
    return result;
}

std::vector<unsigned char> UINTToBytes(uint64_t number, unsigned int number_of_bytes) {
    std::vector<unsigned char> result;
    result.reserve(number_of_bytes);
    for (unsigned int i = 0; i < number_of_bytes; ++i) {
        unsigned char current_byte = number % 256;
        result.push_back(current_byte);
        number = (number - current_byte) / 256;
    }
    return result;
}

BMPStructure::BMPStructure(unsigned char *bytes) {
    std::memcpy(&identify_the_BMP_, bytes, 2);
    std::memcpy(&size_of_BMP_, &bytes[2], 4);
    std::memcpy(&application_that_creates_the_image_, &bytes[6], 2);
    std::memcpy(&application_that_creates_the_image_2_, &bytes[8], 2);
    std::memcpy(&the_offset_, &bytes[10], 4);
    std::memcpy(&size_of_this_header_, &bytes[14], 4);
    std::memcpy(&bitmap_width_, &bytes[18], 4);
    std::memcpy(&bitmap_height_, &bytes[22], 4);
    std::memcpy(&number_of_color_, &bytes[26], 2);
    std::memcpy(&number_of_bits_per_pixel_, &bytes[28], 2);
    std::memcpy(&compression_method_, &bytes[30], 4);
    std::memcpy(&image_size_, &bytes[34], 4);
    std::memcpy(&horizontal_resolution_, &bytes[38], 4);
    std::memcpy(&vertical_resolution_, &bytes[42], 4);
    std::memcpy(&colors_in_palette_, &bytes[46], 4);
    std::memcpy(&number_of_important_color_, &bytes[50], 4);
    size_in_bytes_int_format_ = BytesToUINT(size_of_BMP_.begin(), 4);
    image_width_int_format_ = BytesToUINT(bitmap_width_.begin(), 4);
    image_height_int_format_ = BytesToUINT(bitmap_height_.begin(), 4);
    compression_type_ = BytesToUINT(compression_method_.begin(), 4);
    bits_per_pixel_ = BytesToUINT(number_of_bits_per_pixel_.begin(), 2);
    full_structure_ = std::vector<unsigned char>(54);
    std::memcpy(&(full_structure_[0]), bytes, 54);
}

void BMPStructure::SetSizeInt(uint64_t new_size) {
    size_in_bytes_int_format_ = new_size;
    std::vector<unsigned char> number_in_bytes = UINTToBytes(new_size, 4);
    std::memcpy(&size_of_BMP_, &(number_in_bytes[0]), 4);
    std::memcpy(&(full_structure_[2]), &(number_in_bytes[0]), 4);
}

void BMPStructure::SetWidthInt(unsigned int new_width) {
    image_width_int_format_ = new_width;
    std::vector<unsigned char> number_in_bytes = UINTToBytes(new_width, 4);
    std::memcpy(&bitmap_width_, &(number_in_bytes[0]), 4);
    std::memcpy(&(full_structure_[18]), &(number_in_bytes[0]), 4);
}

void BMPStructure::SetHeightInt(unsigned int new_height) {
    image_height_int_format_ = new_height;
    std::vector<unsigned char> number_in_bytes = UINTToBytes(new_height, 4);
    std::memcpy(&bitmap_height_, &(number_in_bytes[0]), 4);
    std::memcpy(&(full_structure_[22]), &(number_in_bytes[0]), 4);
}

std::vector<unsigned char> BMPStructure::GetStructureInBytes() const {
    return full_structure_;
}
