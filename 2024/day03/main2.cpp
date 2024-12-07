#include <cstdint>
#include <regex>
#include <iostream>

int main() {
    std::string line;
    int64_t sum = 0;

    bool enable = true;
    while (std::getline(std::cin, line)) {
        std::regex regex("do\\(\\)|don't\\(\\)|mul\\((\\d+),(\\d+)\\)");

        auto mul = 
            std::sregex_iterator(line.begin(), line.end(), regex);
        auto mul_end = std::sregex_iterator();

        while (mul != mul_end) {
            std::smatch sm = *mul;
            if (sm[0] == "do()") enable = true;
            else if (sm[0] == "don't()") enable = false;
            else if (enable) sum += std::stoi(sm[1]) * std::stoi(sm[2]);
            mul++;
        }
    }

    std::cout << sum << std::endl;
}
