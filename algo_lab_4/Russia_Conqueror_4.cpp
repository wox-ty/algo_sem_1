#include "iostream"
#include "vector"
#include "string"

class Heap {
private:
    std::vector<std::pair<long, long>> a;


    void siftUP(long index) {
        while (index != 0 && a[index].first >= a[(index - 1) / 2].first) {
            if (a[index].first == a[(index - 1) / 2].first){
                if (a[index].second > a[(index - 1) / 2].second){
                    std::swap(a[index], a[(index - 1) / 2]);
                    index = (index - 1) / 2;
                }
            }
            else {
                std::swap(a[index], a[(index - 1) / 2]);
                index = (index - 1) / 2;
            }
        }
    }

    void siftDown(long index) {
        while (2 * index + 1 < a.size()) {
            long maxChild = 2 * index + 1;
            if (maxChild + 1 < a.size() && a[maxChild].first < a[maxChild + 1].first) {
                ++maxChild;
            }

            if (a[index].first >= a[maxChild].first) {
                if (a[index].first == a[maxChild].first) {
                    if (a[index].second < a[maxChild].second) {
                        std::swap(a[index], a[(index - 1) / 2]);
                    }
                    else{
                        break;
                    }
                }
                else {
                    break;
                }
            }

            std::swap(a[index], a[maxChild]);
            index = maxChild;

        }
    }

public:
    Heap() {}

    Heap(std::vector<std::pair<long, long>> &values) {
        a = values;
        for (long i = a.size() - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    void push(std::pair<long, long> value) {
        a.push_back(value);
        siftUP(a.size() - 1);
    }

    std::pair<long, long> pop() {
        std::pair<long, long> value = a[0];
        a[0] = a[a.size() - 1];
        a.pop_back();
        siftDown(0);

        return value;
    }

    std::pair<long, long> peek() {
        return a[0];
    }
};

int main() {
    long n;
    std::cin >> n;
    Heap rating;
    Heap cash;
    long idx, rat, pay;
    for (long i = 0; i < n; ++i) {
        std::cin >> idx >> rat >> pay;

        rating.push(std::pair(rat, idx));
        cash.push(std::pair(pay, idx));
    }

    long m;
    std::cin >> m;
    std::string ans;
    long coun = 0;
    std::vector<long> city;
    std::vector<long> res;


    for (long j = 0; j < n; ++j) {
        if (rating.peek().second == cash.peek().second) {
            res.push_back(rating.pop().second);
            cash.pop();
            continue;
        }

        if (coun < m) {
            std::cin >> ans;
            ++coun;

            if (ans == "YES") {
                if (rating.peek().second == cash.peek().second) {
                    res.push_back(rating.pop().second);
                    city.push_back(cash.pop().second);
                } else {
                    city.push_back(rating.peek().second);
                    res.push_back(rating.pop().second);
                }
            } else if (ans == "NO") {
                city.push_back(rating.pop().second);
            }
        }
        else{
            rating.pop();
        }
    }

    for (long index: city) {
        std::cout << index << " ";
    }

    std::cout << "\n";

    for (long index: res) {
        std::cout << index << " ";
    }

    return 0;
}