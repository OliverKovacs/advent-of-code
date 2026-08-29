#include <cassert>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

#define table_t std::vector<std::vector<int64_t>>

std::string read()
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int64_t sum(std::stringstream &ss)
{
    int64_t x, res = 0;
    for (ss >> x; x != -1; ss >> x)
        res += x;
    return res;
}

int64_t prod(std::stringstream &ss)
{
    int64_t x, res = 1;
    for (ss >> x; x != -1; ss >> x)
        res *= x;
    return res;
}

int main()
{
    std::vector<std::string> orig;
    read();

    for (std::string str = read(); str != ""; str = read())
        orig.push_back(str);

    size_t w = 0;
    for (auto e : orig)
        w = std::max(w, e.size());

    for (auto &e : orig)
        while (e.size() < w)
            e += " ";

    std::string transposed;

    for (int32_t i = 0; i < w; i++) {
        bool nl = true;
        for (int32_t j = 0; j < orig.size() - 1; j++) {
            transposed += orig[j][i];
            if (orig[j][i] != ' ')
                nl = false;
        }
        if (nl)
            transposed += "-1";
        transposed += "\n";
    }
    transposed += "-1\n";

    std::stringstream ss(transposed);
    std::string ops = orig[orig.size() - 1];
    int64_t res = 0;
    for (auto c : ops) {
        if (c == '+')
            res += sum(ss);
        if (c == '*')
            res += prod(ss);
    }
    std::cout << res << std::endl;
}
