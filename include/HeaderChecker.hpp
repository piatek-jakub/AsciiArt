#ifndef HEADER_CHECKER_HPP
#define HEADER_CHECKER_HPP

#include <string>

class HeaderChecker {
public:
    static std::string detectType(const std::string& filepath);
};

#endif // HEADER_CHECKER_HPP