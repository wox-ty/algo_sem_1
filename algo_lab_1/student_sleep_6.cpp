#include "iostream"

int main() {
    int N = 0, lsum, rsum;
    std::cin >> N;
    int days[N];
    int opop[N + 1], sum = 0;
    bool check = false;

    opop[0] = 0;
    for (int h = 0; h < N; ++h) {
        std::cin >> days[h];
    }

    for (int i = 0; i < N; ++i) {
        sum = sum + days[i];
        opop[i + 1] = sum;
    }

    if (N == 1){
        std::cout << 0;
    }
    else{
        for (int i = 0; i < N; ++i) {
            rsum = opop[N] - opop[i+1];
            lsum = opop[i];
            if (rsum == 0 && lsum == 0){
                std::cout << i;
                check = true;
                break;
            }
            else if (i != N-1) {
                if (lsum == rsum) {
                    std::cout << i;
                    check = true;
                    break;
                }
            }
        }

        if (check == false) {
            std::cout << -1;
        }
    }
    return 0;
}