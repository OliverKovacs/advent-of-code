#include <cstdint>
#include <iostream>
#include <vector>

char get(const std::vector<std::string> &field, int32_t x, int32_t y) {
    if (y < 0 && field.size() <= y) return '\0';
    if (x < 0 && field[0].size() <= x) return '\0';
    return field[y][x];
}

bool read(
    const std::vector<std::string> &f,
    const std::string &t,
    int32_t x,
    int32_t y,
    int32_t dx,
    int32_t dy
) {
    for (int32_t i = 0; i < t.size(); i++) {
        if (get(f, x + i * dx, y + i * dy) != t[i]) return false;
    }
    return true;
}

int find(const std::vector<std::string> &f, int32_t x, int32_t y) {
    const std::string target = "XMAS";
    int32_t count = 0;
    for (int32_t i = 0; i < 9; i++) {
        if (i == 4) continue;
        int32_t dx = i % 3 - 1;
        int32_t dy = i / 3 - 1;
        count += read(f, target, x, y, dx, dy);
    }
    return count;
}

int main() {
    std::string line;
    std::vector<std::string> field;
    while (std::getline(std::cin, line)) field.push_back(line);

    int64_t sum = 0;
    for (int32_t i = 0; i < field.size(); i++) {
        for (int32_t j = 0; j < field[0].size(); j++)
            sum += find(field, j, i);
    }

    std::cout << sum << std::endl;
}
