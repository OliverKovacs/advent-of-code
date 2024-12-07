#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

int32_t signum(int32_t x) {
    return (x > 0) - (x < 0);
}

int32_t get(std::vector<int32_t> &v, int32_t i, int32_t x) {
    return v[i + (i >= x)];
}

bool is_safe_drop(std::vector<int32_t> v, int32_t x) {
    int32_t delta = get(v, 1, x) - get(v, 0, x);
    const int32_t dir = signum(delta);
    if (dir == 0 || std::abs(delta) > 3) return false;
    for (int32_t i = 2; i < v.size() - 1; i++) {
        delta = get(v, i, x) - get(v, i - 1, x);
        if (dir != signum(delta) || std::abs(delta) > 3) return false;
    }
    return true;
}

bool is_safe(std::istringstream &is) {
    std::vector<int32_t> seq;
    int32_t tmp;
    while(is >> tmp) seq.push_back(tmp);

    for (int i = 0; i <= seq.size(); i++) {
        if (is_safe_drop(seq, i)) return true;
    }
    return false;
}

int main() {
    std::string line;
    int32_t sum = 0;
    while (std::getline(std::cin, line)) {
        std::istringstream is(line);
        sum += is_safe(is);
    }
    std::cout << sum << std::endl;
}

