#include "iostream"
#include "string"
#include "vector"


class Heap {
private:
    std::vector<std::pair<long , long>> a;
    long size = 0;

public:

    Heap() = default;

    void siftUp(long index) {
        while (index != 0 && a[index].first < a[(index - 1) / 2].first) {

            std::swap(a[index], a[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void siftDown(long index) {
        while (2 * index + 1 < a.size()) {
            long minChild = 2 * index + 1;
            if (minChild + 1 < a.size() && a[minChild].first > a[minChild + 1].first) {
                ++minChild;
            }

            if (a[index].first <= a[minChild].first) {
                break;
            }

            std::swap(a[index], a[minChild]);
            index = minChild;
        }
    }

    Heap(std::vector<std::pair<long, long >> &values) {
        a = values;
        for (long i = a.size() - 1; i >= 0; --i) {
            siftDown(i);
        }
        size = values.size();
    }

    void push(std::pair<long, long> val) {
        a.push_back(val);
        siftUp(a.size() - 1);
        ++size;
    }

    std::pair<long, long> pop() {
        std::pair <long, long> value = std::pair(a[0].first, a[0].second);
        a[0] = a[a.size() - 1];
        a.pop_back();
        siftDown(0);
        --size;
        return value;
    }

    long GetSize(){
        return size;
    }

    void siftUp_time(long index) {
        while (index != 0 && a[index].second < a[(index - 1) / 2].second) {

            std::swap(a[index], a[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void siftDown_time(long index) {
        while (2 * index + 1 < a.size()) {
            long minChild = 2 * index + 1;
            if (minChild + 1 < a.size() && a[minChild].second > a[minChild + 1].second) {
                ++minChild;
            }

            if (a[index].second <= a[minChild].second) {
                break;
            }

            std::swap(a[index], a[minChild]);
            index = minChild;
        }
    }

    void push_time(std::pair<long, long> val) {
        a.push_back(val);
        siftUp_time(a.size() - 1);
        ++size;
    }

    std::pair<long, long> pop_time() {
        std::pair <long, long> value = std::pair(a[0].first, a[0].second);
        a[0] = a[a.size() - 1];
        a.pop_back();
        siftDown_time(0);
        --size;
        return value;
    }

    std::pair<long, long> ShowRoot(){
        return a[0];
    }

    void update(long value){
        a[0].second = value;
    }
};


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long n , m;
    std::cin >> n >> m;
    std::vector<std::pair<long, long>> shaver;
    shaver.resize(n);
    long x;
    for (long i = 0; i < n; ++i){
        std::cin >> x;
        shaver[i].first = x;
        shaver[i].second = 1;
    }
    Heap busye;
    Heap shavermen(shaver);

    long sum = 0;
    long st, en;
    for (long i = 0; i < m; ++i){
        std::cin >> st >> en;
        if (busye.GetSize() != 0 && st >= busye.ShowRoot().second){
            while(busye.GetSize() != 0 && st >= busye.ShowRoot().second) {
                shavermen.push(busye.pop_time());
            }
        }
        if (shavermen.GetSize() == 0){
            continue;
        }
        shavermen.update(st);
        sum += shavermen.ShowRoot().first * en;
        std::pair<long, long> tmp = shavermen.pop();
        tmp.second += en;
        busye.push_time(tmp);
    }



    std::cout << sum;

    return 0;
}