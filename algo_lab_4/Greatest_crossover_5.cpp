#include "iostream"

void max_heapify(long *arr, int size, int i){
    int left = 2*i;
    int right = 2*i + 1;

    int largest = i;

    if (left < size && arr[left] > arr[i]){
        largest = left;
    }

    if (right < size && arr[right] > arr[largest]){
        largest = right;
    }

    if (largest != i){
        std::swap(arr[i], arr[largest]);
        max_heapify(arr, size, largest);
    }
}

void build_heap(long *arr, int size){
    for (int i = size/2; i > 0; --i) {
        max_heapify(arr, size, i);
    }
}

void heap_sort(long *arr, int size){
    for (int i = size - 1; i > 0; --i){
        std::swap(arr[0], arr[i]);
        max_heapify(arr, i, 0);
    }
}

int main(){
    int n;
    std::cin >> n;
    long data[n+1];
    data[0] = -99;
    for (int i = 1; i < n+1; ++i){
        std::cin >> data[i];
    }

    build_heap(data, n+1);

    //heap_sort(data, n+1);

    for(int i = 1; i < n+1; ++i){
        std::cout << data[i] << " ";
    }

    return 0;
}