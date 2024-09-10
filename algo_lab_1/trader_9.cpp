#include "iostream"
#include "cmath"

int main() {
    long long X, Y;
    int counter = 0;
    long long binar;
    int u = 60;

    std::cin >> X >> Y;

    for (int a = 1; a < u; ++a) {

        for (int b = 1; b < u; ++b) {

            if (a + b > u) {
                break;
            }

            for (int c = 1; c < u; ++c) {

                if (a + b + c > u) {
                    break;
                }

                binar = 0;

                for (int e = (a + b + c) - c; e < (a + b + c); ++e) {
                    binar += pow(2, e);
                }

                for (int d = 0; d < a; ++d) {
                    binar += pow(2, d);
                }

                if (binar > Y){
                    break;
                }

                if ((binar >= X) && (binar <= Y)) {
                    ++counter;
                }
            }
        }
    }

    std::cout << counter;

    return 0;
}