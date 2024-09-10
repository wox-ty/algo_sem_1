#include "iostream"


void counting_sort(int *A, int n) {

    int k = 0;
    for (int x = 0; x < n; ++x) {
        if (A[x] > k) {
            k = A[x];
        }
    }

    int *C = new int[k];
    ++k;

    for (int number = 0; number < k; ++number) {
        C[number] = 0;
    }

    for (int i = 0; i < n; ++i) {
        ++C[A[i]];
    }


    int pos = 0;
    for (int number = 0; number < k; ++number) {
        while (C[number] != 0) {
            A[pos] = number;
            --C[number];
            ++pos;
        }
    }
}

void q_sort(int B[], int l, int r) {
    int i = l;
    int j = r;
    int m = (B[l] + B[r]) / 2;
    while (i <= j) {
        while (B[i] < m) {
            ++i;
        }
        while (B[j] > m) {
            --j;
        }
        if (i <= j) {
            int x = B[i];
            B[i] = B[j];
            B[j] = x;
            ++i;
            --j;
        }
    }
    if (l < j) {
        q_sort(B, l, j);
    }
    if (r > i) {
        q_sort(B, i, r);
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;

    int women[n];
    int man[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> women[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> man[i];
    }

    int pairs[n * n];
    int a = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pairs[a] = women[i] + man[j];
            ++a;
        }
    }

//    for(int i = 0; i < n*n; ++i){
//        std::cout << pairs[i] << " ";
//    }
//    std::cout << "\n";

    //counting_sort(pairs, n*n);
    q_sort(pairs, 0, n * n);

    for (int i = 0; i < n * n; ++i) {
        std::cout << pairs[i] << " ";
    }
    std::cout << "\n" << pairs[k - 1] << "\n";

/////////////////////////////////////////////////////////////////////////////////////

    counting_sort(women, n);
    counting_sort(man, n);

    int Res[k*k];
    int z = 0;
    int i = 0, j = 0;
    int tmp1, tmp2;
    int alarm = 0;
    // 1 2 2 3 5
    // 1 2 3 4 8

    // 1  1 2 2  1 2 2 3  1 2 2 4  2 2 3 5  3 5  5  1 5  2  2   3   5
    // 1  2 1 1  3 2 2 1  4 3 3 2  4 4 3 1  4 2  3  8 4  8  8   8   8

    // 2  3 3 3  4 4 4 4  5 5 5 5  6 6 6 6  7 7  8  9 9  10 10  11  13

    // 0  1 2 3  4 5 6 7  8 9 0 1  2 3 4 5  6 7  8  9 0  1  2   3   4

    int diff_sums[10] = {2, 3, 4 ,5, 6, 7, 9, 10, 11, 13};



    int s = 0;

    // 3 и 1 нет среди 4

    while (z < k) {
        Res[z] = diff_sums[s];

        ++z;

        tmp1 = i;
        tmp2 = 0;
        std::cout << s << "\n";
        while(true){
            std::cout << "hello" << " " << tmp1 << " " << tmp2 << "\n";
            if((women[tmp1]+man[tmp2]) == diff_sums[s] && (tmp2 != j)){
                Res[z] = women[tmp1]+man[tmp2];
                ++tmp2;
                ++z;
            }
            else if (tmp1 > n || tmp2 > n){
                break;
            }
            else if (tmp2 == j){
                ++tmp2;
            }
            else if(women[tmp1]+man[tmp2] > diff_sums[s]){
                break;
            }
//            else if (women[tmp1]+man[tmp2] == diff_sums[s-1]) {
//                Res[z] = women[tmp1] + man[tmp2];
//                ++tmp2;
//                ++z;
//            }
            else{
                ++tmp2;
            }
        }

        std::cout << "end 1sd" << "\n" << "\n";

        tmp1 = 0;
        tmp2 = j;
        while(true){
            std::cout << "bye" << " " << tmp1 << " " << tmp2 << "\n";
            if((women[tmp1]+man[tmp2] == diff_sums[s]) && (tmp1 != i)){
                Res[z] = women[tmp1]+man[tmp2];
                ++tmp1;
                ++z;
            }
            else if (tmp1 > n || tmp2 > n){
                break;
            }
            else if (tmp1 == i){
                ++tmp1;
            }
            else if(women[tmp1]+man[tmp2] > diff_sums[s]){
                break;
            }
//            else if (women[tmp1]+man[tmp2] == diff_sums[s-1]) {
//                Res[z] = women[tmp1] + man[tmp2];
//                ++tmp1;
//                ++z;
//            }
            else{
                ++tmp1;
            }
        }
        std::cout << "end 2nd" << "\n" <<"\n";

        ++i;
        ++j;

        ++s;
    }

    std::cout << "\n";
    for (int m = 0; m < k; ++m) {
        std::cout << Res[m] << " ";
    }
    std::cout << "\n" << Res[z - 1];

    return 0;
}