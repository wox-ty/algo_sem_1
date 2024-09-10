#include "iostream"


int main() {
    int N;
    std::cin >> N;
    int koef[N];

    char pere[N];
    for (int i = 0; i < N; ++i) {
        pere[i] = ' ';
    }

    int peregorodki = 0;

    for (int i = 0; i < N; ++i) {
        std::cin >> koef[i];
    }

    int a, b, n, kounter, nomer_last, lishnie;

    for (int x = 0; x < N - 1; ++x) {
        n = 0;
        kounter = 0;
        lishnie = 0;
        nomer_last = 0;
        for (int i = x+1; i < N; ++i) {
            if (pere[i] == '|'){
                break;
            }
            if (koef[x] == koef[x + 1]) {
                ++peregorodki;
                pere[x] = '|';
                break;
            }
            if (koef[x] % 2 == 1 && koef[x + 1] % 2 == 1) {
                ++peregorodki;
                pere[x] = '|';
                break;
            }
//            if ((koef[x] & koef[i]) != 0){
//                ++peregorodki;
//                pere[x] = '|';
//                break;
//            }
            a = koef[x];
            b = koef[i];
            while (a != 0 || b != 0) {
                if ((a % 2) && (b % 2)) {
                    ++peregorodki;
//                    pere[x] = '|';
                    n = 1;
                    ++kounter;
                    nomer_last = i;
                    break;
                }
                a = a >> 1;
                b = b >> 1;
            }
            if (n == 1){
                ++lishnie;
            }
        }
//        peregorodki -= lishnie;
        pere[x + nomer_last - 1] = '|';
    }
    for (int i = 0; i < N; ++i) {
        std::cout << koef[i] << " " << pere[i] << " ";
    }
    if (peregorodki == 0){
        ++peregorodki;
    }
    std::cout << "\n" << kounter << " " << nomer_last;
    std::cout << "\n" << "peregorodki: " << peregorodki;

    return 0;
}