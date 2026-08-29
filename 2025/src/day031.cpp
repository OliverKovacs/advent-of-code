#include <cassert>
#include <cstdint>
#include <cmath>
#include <iostream>

#define N 100

int32_t c2i(char c)
{
    assert('0' <= c && c <= '9');
    return c - '0';
}

int64_t solve(std::string str)
{
    int32_t b1 = -1;
    int32_t b2 = -1;
    for (size_t i = 0; i < str.size() - 1; i++) {
        if (b1 < c2i(str[i])) {
            b1 = c2i(str[i]);
            b2 = c2i(str[i + 1]);
        }
        if (b2 < c2i(str[i + 1]))
            b2 = c2i(str[i + 1]);
    }

    return 10 * b1 + b2;
}

int main()
{
    int64_t sum = 0;
    std::string str;
    for (std::cin >> str; str != "X"; std::cin >> str)
        sum += solve(str);

    std::cout << sum << std::endl;
}
