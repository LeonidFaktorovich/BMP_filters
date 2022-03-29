#pragma once

#include <array>
#include <cstdint>
#include <vector>

uint64_t BytesToUINT(unsigned char* bytes, unsigned int number_of_bytes);

std::vector<unsigned char> UINTToBytes(uint64_t number, unsigned int number_of_bytes);

class ImageStructure {
public:
    uint64_t GetSizeInt() const;
    unsigned int GetWidthInt() const;
    unsigned int GetHeightInt() const;
    unsigned int GetCompressionInt() const;
    unsigned int GetBitsPerPixel() const;
    virtual void SetSizeInt(uint64_t new_size) = 0;
    virtual void SetWidthInt(unsigned int new_width) = 0;
    virtual void SetHeightInt(unsigned int new_height) = 0;
    virtual std::vector<unsigned char> GetStructureInBytes() const = 0;
    virtual ~ImageStructure() = default;

protected:
    uint64_t size_in_bytes_int_format_ = 0;
    unsigned int image_width_int_format_ = 0;
    unsigned int image_height_int_format_ = 0;
    unsigned int compression_type_ = 0;
    unsigned int bits_per_pixel_ = 0;
};

class BMPStructure : public ImageStructure {
public:
    BMPStructure(unsigned char* bytes);
    void SetSizeInt(uint64_t new_size) override;
    void SetWidthInt(unsigned int new_width) override;
    void SetHeightInt(unsigned int new_height) override;
    std::vector<unsigned char> GetStructureInBytes() const override;

private:
    std::vector<unsigned char> full_structure_;
    std::array<unsigned char, 2> identify_the_BMP_;
    std::array<unsigned char, 4> size_of_BMP_;
    std::array<unsigned char, 2> application_that_creates_the_image_;
    std::array<unsigned char, 2> application_that_creates_the_image_2_;
    std::array<unsigned char, 4> the_offset_;
    std::array<unsigned char, 4> size_of_this_header_;
    std::array<unsigned char, 4> bitmap_width_;
    std::array<unsigned char, 4> bitmap_height_;
    std::array<unsigned char, 2> number_of_color_;
    std::array<unsigned char, 2> number_of_bits_per_pixel_;
    std::array<unsigned char, 4> compression_method_;
    std::array<unsigned char, 4> image_size_;
    std::array<unsigned char, 4> horizontal_resolution_;
    std::array<unsigned char, 4> vertical_resolution_;
    std::array<unsigned char, 4> colors_in_palette_;
    std::array<unsigned char, 4> number_of_important_color_;
};