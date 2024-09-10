#include "iostream"
#include <string>


void countSort(std::string a[], int size, int k) {
    int z = 257;
    std::string *b = new std::string[size];
    int *c = new int[z];


    for (int i = 0; i < z; i++) {
        c[i] = 0;
    }

    for (int j = 0; j < size; j++) {
        if (k < a[j].size()) {
            c[(int) (unsigned char) a[j][k] + 1]++;
        } else {
            c[0]++;
        }
    }

    for (int f = 1; f < z; f++) {
        c[f] += c[f - 1];
    }

    for (int r = size - 1; r >= 0; r--) {
        if (k < a[r].size()) {
            b[c[(int) (unsigned char) a[r][k] + 1] - 1] = a[r];
        } else {
            c[0]++;
        }

        if (k < a[r].size()) {
            c[(int) (unsigned char) a[r][k] + 1]--;
        } else {
            c[0]--;
        }
    }

    for (int l = 0; l < size; l++) {
        a[l] = b[l];
    }

    delete[] b;
    delete[] c;
}


void radix_sort(std::string b[], int r, int t, int k) {
    for (int i = k - 1; i > k - t - 1; i--) {
        countSort(b, r, i);
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k, t;
    std::cin >> n >> k >> t;

    std::string test[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> test[i];
    }

    radix_sort(test, n, t, k);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            std::cout << test[i][j];
        }
        std::cout << "\n";
    }
    return 0;
}