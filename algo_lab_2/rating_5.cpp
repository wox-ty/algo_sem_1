#include "iostream"

long int counter = 0;

void merge(long B[], long l, long m, long r) {
    long tl1 = 0, tl2 = 0;
    long res[r - l];

    long counter_1 = 0, counter_2 = 0;

    while ((l + tl1 < m) && (m + tl2 < r)) {
        if (B[l + tl1] <= B[m + tl2]) {
            res[tl1 + tl2] = B[l + tl1];
            ++tl1;
            counter_1 += counter_2;
        } else {
            res[tl1 + tl2] = B[m + tl2];
            ++tl2;
            ++counter_2;
        }
    }

    while ((l + tl1) < m) {
        res[tl1 + tl2] = B[l + tl1];
        ++tl1;
        counter_1 += counter_2;
    }
    while ((m + tl2) < r) {
        res[tl1 + tl2] = B[m + tl2];
        ++tl2;
    }
    for (int i = 0; i < (tl1 + tl2); ++i) {
        B[l + i] = res[i];
    }
    counter += counter_1;
}

void merge_sort_recursive(long B[], long l, long r) {
    if ((l + 1) >= r) {
        return;
    }
    long m = (l + r) / 2;
    merge_sort_recursive(B, l, m);
    merge_sort_recursive(B, m, r);
    merge(B, l, m, r);
}


int main() {

    int N;
    std::cin >> N;
    long rat[N];
    for (int i = 0; i < N; ++i) {
        std::cin >> rat[i];
    }

    merge_sort_recursive(rat, 0, N);

//    for (int i = 0; i < N; ++i) {
//        std::cout << rat[i] << " ";
//    }

    std::cout << counter;

    return 0;
}