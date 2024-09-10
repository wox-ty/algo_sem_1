#include <iostream>
#include <string>
#include <vector>

void grayCode(int n, std::vector<int> &result) {
    if (n <= 0) {
        return;
    }

    for (int i = 0; i < (1 << n); i++) {
        result.push_back((i ^ (i >> 1)));
    }
}

std::string To_binary(int s) {
    std::string res;

    while (s != 0) {
        res = (s % 2 == 0 ? "0" : "1") + res;
        s /= 2;
    }
    return res;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> result;
    grayCode(n, result);
    for (auto i: result) {
        std::string tmp = To_binary(i);
        while (tmp.size() != n){
            tmp = '0' + tmp;
        }
        std::cout << tmp << "\n";
    }

    return 0;
}
