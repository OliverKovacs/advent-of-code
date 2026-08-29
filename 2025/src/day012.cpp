#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

#define N 100

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

int main() {
    int32_t pos = 50;
    int32_t cnt = 0;
    int32_t amt, delta;
    char dir;
    for (; std::cin >> dir >> amt; dir != 'X') {
        delta = ((dir == 'L') ? -1 : 1) * amt;
        for (int32_t i = 0; i < std::abs(delta); i++) {
            pos += sgn(delta);
            pos = ((pos % N) + N) % N;
            if (pos == 0)
                cnt++;
        }
    }
    std::cout << cnt << std::endl;
}
