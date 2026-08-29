#include <cstdint>
#include <cmath>
#include <iostream>

#define N 100

bool is_invalid(int64_t x)
{
    std::string str = std::to_string(x);
    int32_t n = str.size();
    for (int32_t i = 1; i <= n / 2; i++) {
        if (n % i)
            continue;

        for (int32_t j = 0; j * i < n; j++)
            if (str.substr(0, i) != str.substr(j * i, i))
                goto continue_outer;

        return true;
        continue_outer:
    }
    return false;
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
