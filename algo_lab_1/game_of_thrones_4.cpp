#include "iostream"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m, q;
    int k = 0, x = 1, h = 1;
    bool check;

    std::cin >> n >> m >> q;

    unsigned int all_ser[n * m][2];

    int a, c;
    for (int b = 0; b < q; ++b) {
        std::cin >> a >> c;
        if (a == 1) {
            all_ser[m * c - a - (m - 1)][0] = -1;
            all_ser[m * c - a - (m - 1)][1] = -1;
            continue;
        }
        all_ser[(c - 1) * m + a - 1][0] = -1; // придумать зависимость
        all_ser[(c - 1) * m + a - 1][1] = -1;

    }

    for (int i = 0; i < (n * m); ++i) {
        check = false;
        if (x == m + 1) {
            x = 1;
            ++h;
        }
        if (all_ser[i][0] == -1 && all_ser[i][1] == -1) {
            ++x;
            ++k;
            continue;
        }

        all_ser[i][0] = x;
        all_ser[i][1] = h;
        ++x;
    }


    std::cout << n * m - k << "\n";

    for (int i = 0; i < (n * m); ++i) {
        if (all_ser[i][0] == -1 && all_ser[i][1] == -1) {
            continue;
        }
        std::cout << all_ser[i][0] << " " << all_ser[i][1] << "\n";
    }

    return 0;
}