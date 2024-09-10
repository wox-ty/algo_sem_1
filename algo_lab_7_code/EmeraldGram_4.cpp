#include <iostream>
#include <string>
#include <vector>


std::string decodeHamming(std::string coded_mes) {
    int m_size = coded_mes.size();
    int control_bits = 0;
    while ((1 << control_bits) < m_size + control_bits + 1) {
        control_bits++;
    }

    int error_pos = 0;

    for (int i = 0; i < control_bits; i++) {
        int bit = 0;

        for (int j = (1 << i); j <= m_size; j += (1 << (i + 1))) {
            for (int k = j; k <= std::min(j + (1 << i) - 1, m_size); k++) {
                bit ^= (coded_mes[k - 1] - '0');
            }
        }

        error_pos += bit * (1 << i);
    }

    if (error_pos > 0) {
        if (coded_mes[error_pos - 1] == '0') {
            coded_mes[error_pos - 1] = '1';
        } else {
            coded_mes[error_pos - 1] = '0';
        }
    }

    std::string result;
    for (int i = 0; i < m_size; i++) {
        if ((i + 1) & i) {
            result += coded_mes[i];
        }
    }

    return result;
}

int main() {
    int n;
    std::cin >> n;
    std::string message;
    std::string decoded;
    std::vector<std::string> ans;
    for (int i = 0; i < n; ++i){
        std::cin >> message;
        decoded = decodeHamming(message);
        ans.push_back(decoded);
    }

    for (auto i : ans){
        std::cout << i << "\n";
    }

    return 0;
}