#include <cstdint>
#include <cmath>
#include <iostream>

#define N 100

bool is_invalid(int64_t x)
{
    std::string str = std::to_string(x);
    int32_t n = str.size();
    return ((n & 1) == 0) && str.substr(0, n / 2) == str.substr(n / 2);
}

int main()
{
    int64_t l, r, sum = 0;
    char c = ',';
    do {
        std::cin >> l >> c >> r >> c;
        for (; l <= r; l++)
            if (is_invalid(l))
                sum += l;
    } while (c != 'X');

    std::cout << sum << std::endl;
}
