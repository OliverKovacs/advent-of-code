#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int32_t> a;
    std::vector<int32_t> b;

    int32_t tmp;
    while (std::cin >> tmp) {
        a.push_back(tmp);
        std::cin >> tmp;
        b.push_back(tmp);
    }

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    int32_t sum = 0;
    for (auto [e1, e2] : std::views::zip(a, b)) {
        sum += std::abs(e1 - e2);
    }
    std::cout << sum << std::endl;
}
