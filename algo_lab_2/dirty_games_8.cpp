#include "iostream"
#include "random"


int main() {

    srand(time(NULL));

    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int N;
    bool check = true;

    std::cin >> N;

    int Cash[N];
    for (int x = 0; x < N; ++x) {
        std::cin >> Cash[x];
    }

    int y;
    bool sad = false;
    for (int x = 0; x < N; x+=x) {

        y = 0;

        for (int i = 0; i < N - 1; ++i) {

            if (Cash[i] > Cash[i + 1]) {
                --Cash[i];
                ++Cash[i + 1];
                std::swap(Cash[i], Cash[i + 1]);
                if (Cash[i] > Cash[i+1]){
                    sad = true;
                    break;
                }
            } else {
                ++y;
            }
        }

        if (sad){
            std::cout << ":(";
            check = false;
            break;
        }


        if (y == N - 1) {
            for (int i = 0; i < N; ++i) {
                std::cout << Cash[i] << " ";
            }
            check = false;
            break;
        }

    }

    if (check) {
        std::cout << ":(";
    }

    return 0;
}