#include "iostream"

int main() {
    int n;
    std::cin >> n;
    long data[n+1];
    data[0] = 0;
    for (int i = 1; i < n + 1; ++i) {
        std::cin >> data[i];
    }

    for (int j = 1; j < n + 1; ++j) {
        if (2 * j <= n) {
            if (data[j] > data[2 * j]) {
                std::cout << "NO";
                return 0;
            }
        }
        if (2 * j + 1 <= n) {
            if (data[j] > data[2 * j + 1]) {
                std::cout << "NO";
                return 0;
            }
        }
    }

    std::cout << "YES";

    return 0;
}