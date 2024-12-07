#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>

int32_t signum(int32_t x) {
    return (x > 0) - (x < 0);
}

bool is_safe(std::istringstream &is) {
    int32_t tmp;
    int32_t last;
    is >> last;
    is >> tmp;
    int32_t delta = tmp - last;
    const int32_t dir = signum(delta);
    if (dir == 0 || std::abs(delta) > 3) return false;
    last = tmp;
    while(is >> tmp) {
        delta = tmp - last;
        if (dir != signum(delta) || std::abs(delta) > 3) return false;
        last = tmp;
    }
    return true;
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

