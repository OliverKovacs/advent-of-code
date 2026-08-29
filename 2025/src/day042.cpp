#include <cassert>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>

#define field_t std::vector<std::string>

bool get(field_t &F, int32_t x, int32_t y)
{
    if (x < 0 || y < 0 || x >= F[0].size() || y >= F.size())
        return false;

    return F[y][x] == '@';
}

bool is_accessible(field_t &F, int32_t x, int32_t y)
{
    if (!get(F, x, y))
        return false;

    int32_t cnt = 0;
    for (int32_t i = x - 1; i <= x + 1; i++)
        for (int32_t j = y - 1; j <= y + 1; j++)
            cnt += !(i == x && j == y) && get(F, i, j);

    if (cnt >= 4)
        return false;

    F[y][x] = '.';
    return true;
}

int32_t cnt_accessible(field_t &F)
{
    int32_t sum = 0;
    for (int32_t x = 0; x < F[0].size(); x++)
        for (int32_t y = 0; y < F.size(); y++)
            sum += is_accessible(F, x, y);

    return sum;
}

int main()
{
    field_t F;
    std::string str;
    for (std::cin >> str; str != "X"; std::cin >> str)
        F.push_back(str);

    int32_t cnt, sum = 0;
    do {
        cnt = cnt_accessible(F);
        sum += cnt;
    } while (cnt != 0);

    std::cout << sum << std::endl;
}
