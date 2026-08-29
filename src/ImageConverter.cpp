#include "ImageConverter.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

ImageConverter::ImageConverter(double aspect) : fontAspectRatio(aspect) {}

std::pair<double, double> ImageConverter::computeSobel(const ImageLoader& img, int x, int y) const {
    static const int Gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    static const int Gy[3][3] = { {-1, -2, -1}, { 0,  0,  0}, { 1,  2,  1} };

    double gx = 0, gy = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            double lum = img.getPixel(x + dx, y + dy).luminance();
            gx += Gx[dy + 1][dx + 1] * lum;
            gy += Gy[dy + 1][dx + 1] * lum;
        }
    }
    return { std::hypot(gx, gy), std::atan2(gy, gx) };
}

std::vector<std::vector<AsciiPixel>> ImageConverter::convert(const ImageLoader& img, int targetWidth, bool enableSobel) {
    int targetHeight = static_cast<int>((static_cast<double>(img.getHeight()) / img.getWidth()) * targetWidth * fontAspectRatio);
    std::vector<std::vector<AsciiPixel>> asciiGrid(targetHeight, std::vector<AsciiPixel>(targetWidth));

    double scaleX = static_cast<double>(img.getWidth()) / targetWidth;
    double scaleY = static_cast<double>(img.getHeight()) / targetHeight;

    for (int outY = 0; outY < targetHeight; ++outY) {
        for (int outX = 0; outX < targetWidth; ++outX) {
            int srcX = static_cast<int>(outX * scaleX);
            int srcY = static_cast<int>(outY * scaleY);

            Pixel color = img.getPixel(srcX, srcY);
            char selectedChar = ' ';
            bool isEdge = false;

            if (enableSobel) {
                auto [mag, angle] = computeSobel(img, srcX, srcY);
                if (mag > 150.0) {
                    isEdge = true;
                    double deg = angle * 180.0 / 3.14159265358979323846;
                    if (deg < 0) deg += 180.0;

                    if (deg >= 22.5 && deg < 67.5)       selectedChar = '/';
                    else if (deg >= 67.5 && deg < 112.5)  selectedChar = '|';
                    else if (deg >= 112.5 && deg < 157.5) selectedChar = '\\';
                    else                                  selectedChar = '-';
                }
            }

            if (!isEdge) {
                double lum = color.luminance();
                size_t rampIdx = static_cast<size_t>((lum / 255.0) * (ramp.size() - 1));
                selectedChar = ramp[rampIdx];
            }

            asciiGrid[outY][outX] = { selectedChar, color };
        }
    }
    return asciiGrid;
}

void ImageConverter::renderToTerminal(const std::vector<std::vector<AsciiPixel>>& asciiGrid) const {
    for (const auto& row : asciiGrid) {
        for (const auto& cell : row) {
            std::cout << "\x1b[38;2;"
                << static_cast<int>(cell.color.r) << ";"
                << static_cast<int>(cell.color.g) << ";"
                << static_cast<int>(cell.color.b) << "m"
                << cell.ch;
        }
        std::cout << "\x1b[0m\n";
    }
}

void ImageConverter::saveToFile(const std::vector<std::vector<AsciiPixel>>& asciiGrid, const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) return;

    for (const auto& row : asciiGrid) {
        for (const auto& cell : row) {
            outFile << cell.ch;
        }
        outFile << "\n";
    }
}