#include "iostream"


void q_sort(long int B[], int l, int r){
    int i = l;
    int j = r;
    int m = (B[l] + B[r]) / 2;
    while (i <= j){
        while (B[i] < m){
            ++i;
        }
        while (B[j] > m){
            --j;
        }
        if (i <= j){
            int x = B[i];
            B[i] = B[j];
            B[j] = x;
            ++i;
            --j;
        }
    }
    if (l < j){
        q_sort(B, l, j);
    }
    if (r > i){
        q_sort(B, i, r);
    }
}


int main() {
    long int N;
    std::cin >> N;
    long int vetki[N];
    for (int i = 0; i < N; ++i) {
        std::cin >> vetki[i];
    }

    q_sort(vetki, 0, N-1);

    long int res = 0;
    long int max_1 = 0, max_2 = 0;
    bool check;
    check = true;

    for (int x = N - 1; x > 0; --x) {
        if (!check) {
            check = true;
            continue;
        }

        if (max_1 != 0 && max_2 != 0) {
            res += max_2 * max_1;
            max_1 = 0;
            max_2 = 0;
        }

        if (vetki[x] == vetki[x - 1]) {
            if (max_1 < vetki[x]) {
                max_1 = vetki[x];
            } else if (max_2 < vetki[x]) {
                max_2 = vetki[x];
            }
            check = false;

        } else if (vetki[x] - 1 == vetki[x - 1]) {
            if (max_1 < vetki[x]) {
                max_1 = vetki[x] - 1;
            } else if (max_2 < vetki[x]) {
                max_2 = vetki[x] - 1;
            }
            check = false;
        }
    }

    if (max_1 != 0 && max_2 != 0) {
        res += max_2 * max_1;
    }

    std::cout << res;

    return 0;
}