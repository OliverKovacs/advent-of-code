#include <cstdint>
#include <iostream>
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

    int32_t sum = 0;
    for (auto l : a) {
        int32_t count = 0;
        for (auto r : b) count += l == r;
        sum += l * count;
    }
    std::cout << sum << std::endl;
}
