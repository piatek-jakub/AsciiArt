#include "ImageLoader.hpp"
#include "ImageConverter.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string filepath = (argc > 1) ? argv[1] : "sample.jpg";

    auto loader = ImageLoaderFactory::createLoader(filepath);

    if (!loader->load(filepath)) {
        std::cerr << "Failed to load image: " << filepath << "\n";
        return 1;
    }

    ImageConverter converter(0.5);
    auto asciiGrid = converter.convert(*loader, 100, true);

    converter.renderToTerminal(asciiGrid);
    converter.saveToFile(asciiGrid, "output.txt");

    return 0;
}