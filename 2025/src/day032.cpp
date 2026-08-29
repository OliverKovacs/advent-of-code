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

int64_t solve(std::string str, int32_t k, int32_t left)
{
    if (left == 0)
        return 0;

    int32_t b = -1;

    for (size_t i = k; i < str.size() - left + 1; i++)
        if (b < c2i(str[i]))
            b = c2i(str[i]);

    for (size_t i = k; i < str.size() - left + 1; i++)
        if (b == c2i(str[i]))
            return static_cast<int64_t>(pow(10, left - 1)) * b
                + solve(str, i + 1, left - 1);

    assert(false);
}

int main()
{
    int64_t sum = 0;
    std::string str;
    for (std::cin >> str; str != "X"; std::cin >> str)
        sum += solve(str, 0, 12);

    std::cout << sum << std::endl;
}
