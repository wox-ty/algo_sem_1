#include "iostream"


void q_sort(long B[][2], int l, int r){
    int i = l;
    int j = r;
    int m = (B[l][0] + B[r][0]) / 2;
    while (i <= j){
        while (B[i][0] < m){
            ++i;
        }
        while (B[j][0] > m){
            --j;
        }
        if (i <= j){
            std::swap(B[i][0],B[j][0]);
            std::swap(B[i][1], B[j][1]);
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
    int N;
    int maxim = 0;
    std::cin >> N;
    long Arr[N][2];
    for (int x = 0; x < N; ++x) {
        std::cin >> Arr[x][0] >> Arr[x][1];
    }

    q_sort(Arr, 0, N-1);

//    for (int i = 0; i < N; ++i){
//        std::cout << Arr[i][0] << " " << Arr[i][1] << "\n";
//    }
//    std::cout << "\n";

    long int sum = 0;
    long int start = 0;
    long int end;
    for (int x = 0; x < N; ++x) {
        start += Arr[x][0];
        end = Arr[x][1];
        sum += (end - start);
    }

    std::cout << sum;

    return 0;
}
