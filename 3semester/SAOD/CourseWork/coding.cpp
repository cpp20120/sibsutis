#include "coding.hpp"
#include <map>
#include <queue>
#include <vector>
#include <iostream>

struct Node {
    char symbol;
    double probability;
    Node* left;
    Node* right;

    Node(char s, double p) : symbol(s), probability(p), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->probability > b->probability;
    }
};

void buildCodes(Node* root, const std::string& str, std::unordered_map<char, std::string>& codes) {
    if (!root) return;

    if (!root->left && !root->right) {
        codes[root->symbol] = str;
    }

    buildCodes(root->left, str + "0", codes);
    buildCodes(root->right, str + "1", codes);
}

std::unordered_map<char, std::string> ShannonCoding::encode(const std::string& input) {
    std::unordered_map<char, double> frequencies;
    for (char c : input) {
        frequencies[c]++;
    }

    for (auto& [key, value] : frequencies) {
        value /= input.size();
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (const auto& [symbol, probability] : frequencies) {
        pq.push(new Node(symbol, probability));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* combined = new Node('\0', left->probability + right->probability);
        combined->left = left;
        combined->right = right;

        pq.push(combined);
    }

    std::unordered_map<char, std::string> codes;
    buildCodes(pq.top(), "", codes);

    return codes;
}

std::string ShannonCoding::decode(const std::unordered_map<char, std::string>& encoding, const std::string& encodedStr) {
    std::unordered_map<std::string, char> reverseMap;
    for (const auto& [symbol, code] : encoding) {
        reverseMap[code] = symbol;
    }

    std::string decoded;
    std::string current;
    for (char c : encodedStr) {
        current += c;
        if (reverseMap.count(current)) {
            decoded += reverseMap[current];
            current.clear();
        }
    }

    return decoded;
}
