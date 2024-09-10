#include "iostream"

bool Finder(int *chairs, int boyare, int range, int size) {
    int counter = 1;
    int last_seat = chairs[0];

    for (int i = 1; i < size; ++i) {
        if (last_seat + range > chairs[i]) {
            continue;
        } else {
            ++counter;
            last_seat = chairs[i];
        }
    }

    return counter >= boyare;
}

void q_sort(int *B, int l, int r) {
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
            std::swap(B[i], B[j]);
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
    int N, K;
    std::cin >> N >> K;

    int chairs[N];
    for (int i = 0; i < N; ++i) {
        std::cin >> chairs[i];
    }

    q_sort(chairs, 0, N-1);

//    for (int i = 0; i < N; ++i) {
//        std::cout << chairs[i] << " ";
//    }
//    std::cout << "\n";



    int l = 0, r = 1000000000;

    while (l + 1 < r) {

        int mid = l + (r - l) / 2;

        if (Finder(chairs, K, mid, N)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    std::cout << l;

    return 0;
}