#include <cstdint>
#include <regex>
#include <iostream>
#include <sstream>

int main() {
    std::string line;
    int64_t sum = 0;
    while (std::getline(std::cin, line)) {
        std::regex regex("mul\\((\\d+),(\\d+\\))");

        auto mul = 
            std::sregex_iterator(line.begin(), line.end(), regex);
        auto mul_end = std::sregex_iterator();

        while (mul != mul_end) {
            std::smatch sm = *mul;
            std::istringstream is(sm.str());
            sum += std::stoi(sm[1]) * std::stoi(sm[2]);
            mul++;
        }
    }

    std::cout << sum << std::endl;
}
