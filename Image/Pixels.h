#pragma once

#include <cstdint>
#include <vector>

class Pixels {
public:
    Pixels(unsigned char *bytes, uint64_t number_of_bytes, unsigned int image_height, unsigned int image_width,
           unsigned int size_of_block, unsigned int bytes_for_pixel);

    Pixels(const Pixels &pixels);

    Pixels() = default;
    struct PixelRow {
        PixelRow(unsigned int number_of_pixels, unsigned char *current_ptr, unsigned int bytes_in_pixel);

        unsigned int pixels_in_row = 0;
        unsigned char *first_byte = nullptr;
        unsigned int bytes_for_pixel = 0;
        class FloatRepresentation {
        public:
            struct Color {
                Color(unsigned char *byte);
                Color &operator=(float float_value);
                Color &operator=(const Color &other);
                operator float();
                unsigned char *byte;
            };
            FloatRepresentation(unsigned char *bytes, unsigned int number_of_bytes);
            Color Red();
            Color Alpha();
            Color Blue();
            Color Green();
            std::vector<Color> GetFloatValues();

        private:
            unsigned char *bytes_;
            unsigned int number_of_bytes_;
        };
        FloatRepresentation operator[](int32_t number_of_pixel);
    };

    unsigned int GetImageHeight() const;

    unsigned int GetImageWidth() const;

    unsigned int GetSizeOfBlock() const;

    unsigned int GetBytesForPixel() const;

    uint64_t GetNumberOfBytes() const;

    unsigned char *GetBytes();

    void SetBytes(unsigned char *new_bytes);

    PixelRow operator[](int32_t index_of_row);

protected:
    unsigned char *bytes_ = nullptr;
    unsigned int image_height_ = 0;
    unsigned int image_width_ = 0;
    unsigned int size_of_block_ = 4;
    unsigned int bytes_for_pixel_ = 3;
    uint64_t number_of_bytes_ = 0;
};

class PixelsBuilder : public Pixels {
public:
    PixelsBuilder() = default;

    Pixels *Create();

    PixelsBuilder &SetBytes(uint64_t number_of_bytes, unsigned char *bytes);

    PixelsBuilder &SetImageHeight(unsigned int image_height);

    PixelsBuilder &SetImageWidth(unsigned int image_width);

    PixelsBuilder &SetSizeOfBlock(unsigned int size_of_block);

    PixelsBuilder &SetBytesForPixel(unsigned int bytes_for_pixels);
};
