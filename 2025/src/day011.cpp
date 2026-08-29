#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

#define N 100

int main() {
    int32_t pos = 50;
    int32_t cnt = 0;
    int32_t amt;
    char dir;
    for (; std::cin >> dir >> amt; dir != 'X') {
        pos += (dir == 'L' ? -1 : 1) * amt;
        pos = ((pos % N) + N) % N;
        if (pos == 0)
            cnt++;
    }
    std::cout << cnt << std::endl;
}
