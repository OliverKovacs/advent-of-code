#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

bool is_valid (
    std::vector<std::pair<int32_t, int32_t>> &r,
    std::vector<int32_t> &s
) {
    for (int32_t i = 0; i < s.size(); i++) {
        for (int32_t j = i + 1; j < s.size(); j++) {
            for (int32_t k = 0; k < r.size(); k++) {
                if (s[i] == r[k].second && s[j] == r[k].first) return false;
            }
        }
    }
    return true;
}

int main() {
    std::vector<std::pair<int32_t, int32_t>> rules;
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

        if (is_valid(rules, seq)) sum += seq[seq.size() / 2];
        seq.clear();
    }

    std::cout << sum << std::endl;
}

