#pragma once

#include <vector>
#include <string>

namespace str {
    std::vector<int> strstr(const std::string &str, const std::string &temp, int &compares);

    std::vector<int> rabin_losos(const std::string &str, const std::string &temp, int &compares);
} // namespace str