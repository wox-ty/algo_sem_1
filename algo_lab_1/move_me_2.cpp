#include "iostream"

int main() {
    int N, K, p;

    std::cin >> N >> K;

    int arr[N], m[N];
    for (int i = 0; i < N; ++i) {
        std::cin >> arr[i];
    }
    p = K;
    K = abs(K) % N;

    if (p >= 0) {
        //левая часть
        for (int i = 0; i < K; ++i) {
            m[i] = arr[N - K + i];
        }
        //правая часть
        for (int b = 0; b < N - K; ++b) {
            m[b + K] = arr[b];
        }

    } else {
        //правая часть
        for (int i = 0; i < K; ++i) {
            m[N - K + i] = arr[i];
        }

        //левая часть
        for (int b = 0; b < N - K; ++b) {
            m[b] = arr[b + K];
        }
    }

    for (int i = 0; i < N; ++i) {
        std::cout << m[i] << " ";
    }
    return 0;
}