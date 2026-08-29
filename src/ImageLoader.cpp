#include "ImageLoader.hpp"
#include "HeaderChecker.hpp"
#include "stb/stb_image.h"
#include <algorithm>
#include <iostream>

Pixel ImageLoader::getPixel(int x, int y) const {
    x = std::clamp(x, 0, width - 1);
    y = std::clamp(y, 0, height - 1);
    return pixels[y * width + x];
}

bool STBImageLoader::load(const std::string& filepath) {
    int channels = 0;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 3);

    if (!data) {
        std::cerr << "stb_image failed: " << stbi_failure_reason() << "\n";
        return false;
    }

    pixels.resize(width * height);
    for (int i = 0; i < width * height; ++i) {
        pixels[i] = Pixel{
            data[i * 3 + 0],
            data[i * 3 + 1],
            data[i * 3 + 2]
        };
    }

    stbi_image_free(data);
    return true;
}

std::unique_ptr<ImageLoader> ImageLoaderFactory::createLoader(const std::string& filepath) {
    std::string format = HeaderChecker::detectType(filepath);
    if (format == "JPG") return std::make_unique<JPGImageLoader>();
    if (format == "PNG") return std::make_unique<PNGImageLoader>();

    //fallback to STB (BMP, TGA, GIF, ...)
    return std::make_unique<STBImageLoader>();
}