#include "HeaderChecker.hpp"
#include <fstream>

std::string HeaderChecker::detectType(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) return "UNKNOWN";

    unsigned char magic[4] = { 0 };
    file.read(reinterpret_cast<char*>(magic), 4);

    if (magic[0] == 0xFF && magic[1] == 0xD8 && magic[2] == 0xFF) return "JPG";
    if (magic[0] == 0x89 && magic[1] == 'P' && magic[2] == 'N' && magic[3] == 'G') return "PNG";

    return "UNKNOWN";
}