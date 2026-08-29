#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstdint>

struct Pixel {
    uint8_t r{ 0 }, g{ 0 }, b{ 0 };

    double luminance() const {
        return 0.2126 * r + 0.7152 * g + 0.0722 * b;
    }
};

struct AsciiPixel {
    char ch{ ' ' };
    Pixel color;
};

#endif // PIXEL_HPP