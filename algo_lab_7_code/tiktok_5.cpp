#include <iostream>
#include <string>
#include <map>
#include <iomanip>

void arithmetic_encode(std::string input) {
    int len = input.length();
    double low = 0, high = 1, range = 1;
    std::map<char, int> symbol_count;

    for (char c: input) {
        symbol_count[c]++;
    }

    for (char c: input) {
        int symbol_low = 0, symbol_high = 0;

        // Calculate the range for the current symbol
        for (auto it = symbol_count.begin(); it != symbol_count.end(); ++it) {
            if (it->first == c) {
                symbol_high = symbol_low + it->second;
                break;
            }
            symbol_low += it->second;
        }

        // Update the low and high values
        low = low + range * symbol_low / len;
        high = low + range * symbol_high / len;
        range = high - low;
    }

    std::cout << "Encoded value: [" << std::fixed << std::setprecision(6) << low << ", " << high << ")";
}

int main() {
    std::string input;

    std::cout << "Enter a string to encode: ";
    std::getline(std::cin, input);

    arithmetic_encode(input);

    return 0;
}