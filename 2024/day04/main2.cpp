#include <cstdint>
#include <iostream>
#include <vector>

char get(const std::vector<std::string> &field, int32_t x, int32_t y) {
    if (y < 0 && field.size() <= y) return '\0';
    if (x < 0 && field[0].size() <= x) return '\0';
    return field[y][x];
}

bool find(const std::vector<std::string> &f, int32_t x, int32_t y) {
    return get(f, x, y) == 'A' 
        && (get(f, x - 1, y - 1) == 'M' && get(f, x + 1, y + 1) == 'S'
        || get(f, x - 1, y - 1) == 'S' && get(f, x + 1, y + 1) == 'M')
        && (get(f, x - 1, y + 1) == 'M' && get(f, x + 1, y - 1) == 'S'
        || get(f, x - 1, y + 1) == 'S' && get(f, x + 1, y - 1) == 'M');
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
