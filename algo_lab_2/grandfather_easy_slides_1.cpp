#include "iostream"


void ins_sort(int B[], int X){
    for (int j = 1; j < X; ++j){
        int key = B[j];
        int i = j - 1;
        while ((i >= 0) && (B[i] > key)){
            B[i + 1] = B[i];
            --i;
        }
        B[i + 1] = key;
    }
}


int main(){

    int N;
    std::cin >> N;

    int slides[N];
    for (int i = 0; i < N; ++i){
        std::cin >> slides[i];
    }

    ins_sort(slides, N);

    for (int x = 0; x < N; ++x){
        std::cout << slides[x] << " ";
    }

    return 0;
}