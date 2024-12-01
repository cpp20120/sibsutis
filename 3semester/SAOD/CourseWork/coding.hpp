#pragma once

#include <string>
#include <unordered_map>

class ShannonCoding {
public:
    static std::unordered_map<char, std::string> encode(const std::string& input);
    static std::string decode(const std::unordered_map<char, std::string>& encoding, const std::string& encodedStr);
};

