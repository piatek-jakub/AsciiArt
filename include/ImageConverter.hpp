#ifndef IMAGE_CONVERTER_HPP
#define IMAGE_CONVERTER_HPP

#include "ImageLoader.hpp"
#include "Pixel.hpp"
#include <vector>
#include <string>
#include <utility>

class ImageConverter {
private:
    std::string ramp = " .:-=+*#%@";
    double fontAspectRatio = 0.5;

    std::pair<double, double> computeSobel(const ImageLoader& img, int x, int y) const;

public:
    explicit ImageConverter(double aspect = 0.5);

    std::vector<std::vector<AsciiPixel>> convert(const ImageLoader& img, int targetWidth = 80, bool enableSobel = true);
    void renderToTerminal(const std::vector<std::vector<AsciiPixel>>& asciiGrid) const;
    void saveToFile(const std::vector<std::vector<AsciiPixel>>& asciiGrid, const std::string& filename) const;
};

#endif // IMAGE_CONVERTER_HPP