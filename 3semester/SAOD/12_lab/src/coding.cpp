#include "../include/codings.hpp"

#include <cmath>
#include <algorithm>

namespace coding {
    void shennon(std::vector<Table> &arr) {
        std::sort(arr.begin(), arr.end(), [](const Table &a, const Table &b) { return a.probability > b.probability; });
        arr.insert(arr.begin(), { 0 });

        auto pred_it = arr.begin();
        for (auto it = ++arr.begin(); it != arr.end(); ++it) {
            it->q = pred_it->q + pred_it->probability;
            it->code.resize(std::ceil(-std::log2(it->probability)));
            ++pred_it;
        }

        for (Table &symbol : arr) {
            for (int &code : symbol.code) {
                symbol.q *= 2;
                code = symbol.q;
                if (symbol.q > 1) --symbol.q;
            }
        }

        arr.erase(arr.begin());
    }

    static int med(std::vector<Table> &arr, int left, int right) {
        double s_left = 0;
        for (int i = left; i < right; ++i) s_left += arr.at(i).probability;
        double s_right = arr.at(right).probability;
        int median = right;
        while (s_left >= s_right) {
            --median;
            s_left -= arr.at(median).probability;
            s_right += arr.at(median).probability;
        }
        return median;
    }

    static void fano(std::vector<Table> &arr, int left, int right) {
        if (left < right) {
            int median = med(arr, left, right);
            for (int i = left; i <= right; ++i) {
                if (i <= median) arr.at(i).code.push_back(0);
                else arr.at(i).code.push_back(1);
            }
            fano(arr, left, median);
            fano(arr, median + 1, right);
        }
    }

    void fano(std::vector<Table> &arr) {
        std::sort(arr.begin(), arr.end(), [](const Table &a, const Table &b) { return a.probability > b.probability; });
        fano(arr, 0, arr.size() - 1);
    }

    static int up(std::vector<Table> &arr, int n, double q) {
        int j = 0;
        for (int i = n - 1; i > 0; --i) {
            if (arr.at(i - 1).q <= q) arr.at(i).q = arr.at(i - 1).q;
            else {
                j = i;
                break;
            }
        }
        arr.at(j).q = q;
        return j;
    }

    static void down(std::vector<Table> &arr, int n, int j) {
        std::list<int> s = std::move(arr.at(j).code);
        for (int i = j; i < n; ++i) arr.at(i).code = std::move(arr.at(i + 1).code);

        arr.at(n - 1).code = s;
        arr.at(n - 1).code.push_back(0);
        arr.at(n).code = std::move(s);
        arr.at(n).code.push_back(1);
    }

    static void huffman(std::vector<Table> &arr, int n) {
        if (n == 2) {
            arr.at(0).code.push_back(0);
            arr.at(1).code.push_back(1);
        } else {
            double q = arr.at(n - 2).q + arr.at(n - 1).q;
            int j = up(arr, n, q);
            huffman(arr, n - 1);
            down(arr, n - 1, j);
        }
    }

    void huffman(std::vector<Table> &arr) {
        std::size_t n = arr.size();
        std::sort(arr.begin(), arr.end(), [](const Table &a, const Table &b) { return a.probability > b.probability; });
        std::for_each(arr.begin(), arr.end(), [](Table &t) { t.q = t.probability; });
        huffman(arr, arr.size());
    }

    void gilbert_mur(std::vector<Table> &arr) {
        std::sort(arr.begin(), arr.end(), [](const Table &a, const Table &b) { return a.symbol < b.symbol; });

        auto pred_it = arr.begin();
        double pr = 0;
        for (auto it = arr.begin(); it != arr.end(); ++it) {
            it->q = pr + pred_it->probability / 2;
            pr += pred_it->probability;
            it->code.resize(-std::log2(it->probability) + 1);
            ++pred_it;
        }

        for (Table &symbol : arr) {
            for (int &code : symbol.code) {
                symbol.q *= 2;
                code = symbol.q;
                if (symbol.q > 1) --symbol.q;
            }
        }
    }
} // namespace coding
