#include <algorithm>
#include <cmath>

#include "../include/codings.hpp"

inline void shennon(std::vector<coding::Table>& arr) {
    std::sort(arr.begin(), arr.end(), [](const coding::Table& a, const coding::Table& b) { return a.probability > b.probability; });
    arr.insert(arr.begin(), { 0 });

    auto pred_it = arr.begin();
    for (auto it = ++arr.begin(); it != arr.end(); ++it) {
        it->q = pred_it->q + pred_it->probability;
        it->code.resize(std::ceil(-std::log2(it->probability)));
        ++pred_it;
    }

    for (coding::Table& symbol : arr) {
        for (int& code : symbol.code) {
            symbol.q *= 2;
            code = symbol.q;
            if (symbol.q > 1) --symbol.q;
        }
    }

    arr.erase(arr.begin());
}
