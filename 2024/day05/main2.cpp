#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::pair<int32_t, int32_t>> rules;

int32_t corr(int32_t a, int32_t b) {
    for (int32_t k = 0; k < rules.size(); k++) {
        if (b == rules[k].first && a == rules[k].second) return false;
    }
    return true;
}

bool is_valid(std::vector<int32_t> &s) {
    for (int32_t i = 0; i < s.size(); i++) {
        for (int32_t j = i + 1; j < s.size(); j++) {
            if (!corr(s[i], s[j])) return false;
        }
    }
    return true;
}

void sort(std::vector<int32_t> &s) {
    for (int i = 0; i < s.size(); i++) {
        for (int j = i; j < s.size(); j++) {
            if (!corr(s[i], s[j])) std::swap(s[i], s[j]);
        }
    }
}

int main() {
    std::string line;
    char c;

    std::getline(std::cin, line);
    while (line != "") {
        std::istringstream is(line);
        int32_t a, b;
        is >> a >> c >> b;
        rules.push_back(std::make_pair(a, b));
        std::getline(std::cin, line);
    }

    std::vector<int32_t> seq;
    int32_t sum = 0;
    while (std::getline(std::cin, line)) {
        std::istringstream is(line);
        int32_t tmp;
        while (is >> tmp) {
            is.ignore(1, ',');
            seq.push_back(tmp);
        }

        if (!is_valid(seq)) {
            sort(seq);
            sum += seq[seq.size() / 2];
        }
        
        seq.clear();
    }

    std::cout << sum << std::endl;
}

