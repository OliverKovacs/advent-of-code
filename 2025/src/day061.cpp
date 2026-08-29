#include <cassert>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>

#define table_t std::vector<std::vector<int64_t>>

int64_t sum(table_t &T, int32_t k, int32_t m)
{
    int64_t res = 0;
    for (int32_t i = 0; i < m; i++)
        res += T[i][k];
    return res;
}

int64_t prod(table_t &T, int32_t k, int32_t m)
{
    int64_t res = 1;
    for (int32_t i = 0; i < m; i++)
        res *= T[i][k];
    return res;
}

int main()
{
    int64_t n, m;
    std::cin >> n >> m;

    table_t T;
    std::vector<char> ops;
    ops.resize(n);

    for (int32_t i = 0; i < m; i++) {
        std::vector<int64_t> line;
        line.resize(n);
        for (int32_t j = 0; j < n; j++)
            std::cin >> line[j];
        T.push_back(line);
    }

    for (int32_t i = 0; i < n; i++)
        std::cin >> std::ws >> ops[i];

    int64_t res = 0;

    for (int32_t i = 0; i < n; i++)
        res += ops[i] == '+'
            ? sum(T, i, m)
            : prod(T, i, m);

    std::cout << res << std::endl;
}
