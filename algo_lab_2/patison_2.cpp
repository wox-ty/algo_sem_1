#include "iostream"

int i_counter = 0, j_counter = 0, s_counter = 0;
int iter_counter = 0;
void q_sort(int B[], int l, int r){
    iter_counter++;
    int i = l;
    int j = r;
    int m = (B[l] + B[r]) / 2;
    while (i <= j){
        while (B[i] < m){
            ++i;
            ++i_counter;

        }
        while (B[j] > m){
            --j;
            ++j_counter;

        }
        if (i <= j){
            int x = B[i];
            B[i] = B[j];
            B[j] = x;
            ++i;
            --j;
            ++s_counter;

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
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    int slides[N];
    for (int i = 0; i < N; ++i) {
        std::cin >> slides[i];
    }

    q_sort(slides, 0, N - 1);

    for (int x = 0; x < N; ++x) {
        std::cout << slides[x] << " ";
    }

    std::cout << '\n' << i_counter << ' ' << j_counter << ' ' << s_counter << ' ' << iter_counter;

    return 0;
}
/* 7 3 7*/
/* 2 7 7*/

/* 7 3 7 5*/
/* 2 7 7 6*/