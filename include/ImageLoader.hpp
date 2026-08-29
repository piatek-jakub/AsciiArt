#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#include "Pixel.hpp"
#include <string>
#include <vector>
#include <memory>

class ImageLoader {
protected:
    int width{ 0 };
    int height{ 0 };
    std::vector<Pixel> pixels;

public:
    virtual ~ImageLoader() = default;
    virtual bool load(const std::string& filepath) = 0;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    Pixel getPixel(int x, int y) const;
};

class STBImageLoader : public ImageLoader {
public:
    bool load(const std::string& filepath) override;
};

class JPGImageLoader : public STBImageLoader {};
class PNGImageLoader : public STBImageLoader {};

class ImageLoaderFactory {
public:
    static std::unique_ptr<ImageLoader> createLoader(const std::string& filepath);
};

#endif // IMAGE_LOADER_HPP