#include "iostream"


int main() {
    int t, n, ball = 0, u = 0, v = 0;
    char znak[2];

    int min_b, max_b, res_b;

    std::cin >> t;
    int total[1000 * t];

    for (int i = 0; i < t; ++i) {
        min_b = 15;
        max_b = 30;
        std::cin >> n;
        int res_ball[n];
        for (int x = 0; x < n; ++x) {
            std::cin >> znak[0] >> znak[1];
            std::cin >> ball;

            if (znak[0] == '>' && znak[1] == '=' && min_b <= ball)// min порог
            {
                min_b = ball;
            } else if (znak[0] == '<' && znak[1] == '=' && max_b > ball) {
                max_b = ball;
            }

            if (min_b > max_b) {
                res_b = -1;
            } else {
                res_b = min_b;
            }

            res_ball[x] = res_b;
            ++u;

        }
        for (int m = 0; m < n; ++m) {
            total[m + v] = res_ball[m];
        }
        v += n;
    }
    for (int b = 0; b < u; ++b) {
        std::cout << total[b] << "\n";
    }
    return 0;
}