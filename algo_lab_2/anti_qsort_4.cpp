#include "iostream"

int main(){
    int n;
    std::cin >> n;

    int *a = new int[n];
    a[0] = 1;
    a[1] = 2;

    for (int i = 2; i < n; ++i) {
        a[i] = i + 1;
        std::swap(a[i], a[i / 2]);
    }

    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << " ";
    }

    return 0;
}
/*
7
1 4 6 7 2 5 3
*/
/*
1 4 6 7 2 5 3
*/