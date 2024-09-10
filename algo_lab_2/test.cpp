#include <iostream>
#include <vector>

int i_counter = 0, j_counter = 0, s_counter = 0;
int iter_counter = 0;
void q_sort(std::vector<int>& B, int l, int r) {
    iter_counter++;
    if (l >= r) {
        return;  // Если массив из одного элемента, ничего не делать
    }

    // Выбор среднего элемента в качестве опорного
    int mid = l + (r - l) / 2;
    int pivot = B[mid];

    int i = l;
    int j = r;

    // Разбиение массива на основе опорного элемента
    while (i <= j) {
        while (B[i] < pivot) {
            ++i;
            ++i_counter;
        }
        while (B[j] > pivot) {
            --j;
            ++j_counter;
        }
        if (i <= j) {
            std::swap(B[i], B[j]);
            ++i;
            --j;
            ++s_counter;
        }
    }
//    for (auto k : B){
//        std::cout << k << ' ';
//    }
//    std::cout << '\n';
//    std::cout << "--------------\n";
    // Рекурсивная сортировка подмассивов
    if (l < j) {
        q_sort(B, l, j);
    }
    if (i < r) {
        q_sort(B, i, r);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> slides(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> slides[i];
    }

    q_sort(slides, 0, N - 1);

    for (int x : slides) {
        std::cout << x << " ";
    }

    std::cout << '\n' << i_counter << ' ' << j_counter << ' ' << s_counter << ' ' << iter_counter;

    return 0;
}

/* 7 7 6 5*/
/* 15 1 6 6*/