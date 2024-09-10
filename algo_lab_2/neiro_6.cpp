#include "iostream"

int sorter(long long int B[], long long int l, long long int r) {
    long long int y = B[r];

    long long int i = l - 1;

    for (int x = l; x < r; ++x) {
        if (B[x] <= y) {
            ++i;

            long long int z = B[i];
            B[i] = B[x];
            B[x] = z;
        }
    }

    long long int m = B[i + 1];
    B[i + 1] = B[r];
    B[r] = m;

    return i + 1;
}

void q_sort(long long int B[], long long int l, long long int r) {
    if (l < r) {

        long long int py = sorter(B, l, r);

        q_sort(B, l, py - 1);

        q_sort(B, py + 1, r);
    }
}

int main() {
    long int n, m, k;
    std::cin >> n >> m >> k;
    unsigned long int prestige[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> prestige[i];
    }

    long int indexes[k];

    long long int films[m][n];
    long long int score;
    long long int res_score[m], res_copy[m];

    for (int x = 0; x < m; ++x) {
        score = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> films[x][i];
            score += (films[x][i] * prestige[i]);
        }
        score=score%1000000007;
        res_score[x] = score;
        res_copy[x] = score;
    }
    q_sort(res_score, 0, m - 1);

    int a = 0;
    int p;
    int y;
    if (m != k) {
        for (int i = m - 1; i > m - k - 1; --i) {
            y = 0;
            for (int x = 0; x < m; ++x) {

                if (res_score[i] == res_score[i+1]){
                    x = indexes[a-1] + y;
                    ++y;
                }

                if (res_score[i] == res_copy[x]) {
                    indexes[a] = x + 1;
                    ++a;
                    break;
                }
            }
        }
    } else {
        for (int i = m; i > (m - k); --i) {
            p = i - 1;
            if (p < 0) {
                p = 0;
            }
            for (int x = 0; x < m; ++x) {
                if (res_score[p] == res_copy[x]) {
                    indexes[a] = x + 1;
                    ++a;
                    if (a > k) {
                        break;
                    }
                }
            }
        }
    }


    for (int y = 0; y < k; ++y) {
        std::cout << indexes[y] << " ";
    }

    return 0;
}