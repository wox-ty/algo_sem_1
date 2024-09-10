#include <algorithm>
#include "iostream"
#include "vector"
#include "cmath"
#include "tuple"


std::vector<std::tuple<long long, long long, long long>> eratosfen(long long max, long long limit) {
    long long *a = new long long[max + 1];
    for (long long i = 0; i < max + 1; ++i) {
        a[i] = i;
    }
    long long count = 0;
    std::vector<std::tuple<long long,long long, long long>> res;
    for (long long j = 2; j < max + 1; ++j) {
        if (a[j] != 0) {
            res.push_back(std::tuple(a[j], a[j], 1));
            ++count;
            for (long long k = j * j; k < max + 1; k += j) {
                a[k] = 0;
            }
        }
        if (count >= limit){
            break;
        }
    }
    return res;
}

bool is_prime(long long value){
    for (long long i = 2; i <= sqrt(value); ++i){
        if (value % i == 0){
            return false;
        }
    }
    return true;
}

class Heap {
private:
    std::vector<std::tuple<long long, long long,long long>> a;
    long long size = 0;
    long long count = 0;
    std::vector<long long> res;
public:

    Heap() = default;

    void siftUp(long long index) {
        while (index != 0 && std::get<0>(a[index]) < std::get<0>(a[(index - 1) / 2])) {

            std::swap(a[index], a[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void siftDown(long long index) {
        while (2 * index + 1 < a.size()) {
            long long minChild = 2 * index + 1;
            if (minChild + 1 < a.size() && std::get<0>(a[minChild]) > std::get<0>(a[minChild + 1])) {
                ++minChild;
            }

            if (std::get<0>(a[index]) <= std::get<0>(a[minChild])) {
                break;
            }

            std::swap(a[index], a[minChild]);
            index = minChild;
        }
    }

    void siftDown_special(long long index) {
        while (2 * index + 1 < a.size()) {
            long long minChild = 2 * index + 1;
            if (minChild + 1 < a.size() && std::get<1>(a[minChild]) > std::get<1>(a[minChild + 1])) {
                ++minChild;
            }

            if (std::get<1>(a[index]) <= std::get<1>(a[minChild])) {
                break;
            }

            std::swap(a[index], a[minChild]);
            index = minChild;
        }
    }

    Heap(std::vector<std::tuple<long long,long long,long long>> &values) {
        a = values;
        for (long long i = a.size() - 1; i >= 0; --i) {
            siftDown(i);
            ++size;
        }
    }

    void push(std::tuple<long long, long long,long long> value) {
        a.push_back(value);
        siftUp(a.size() - 1);
        ++size;
    }

    std::tuple<long long, long long,long long> pop() {
        std::tuple<long long, long long, long long> value = a[0];
        a[0] = a[a.size() - 1];
        a.pop_back();
        siftDown(0);
        --size;
        ++count;
//        if (is_prime(std::get<0>(value))) {
//            res.push_back(std::get<1>(value));
//        }
//        else{
//            long long tmx = std::get<0>(value);
//            long long coun = 0;
//            while (tmx > 1) {
//                ++coun;
//                tmx = sqrt(tmx);
//            }
//            for (long long i = 0; i < coun; ++i){
//                res.push_back(value.second);
//            }
//        }
        std::get<2>(value) *= 2;
        return value;
    }

    std::tuple<long long, long long,long long> pop_special() {
        std::tuple<long long, long long, long long> value = a[0];
        a[0] = a[a.size() - 1];
        a.pop_back();
        siftDown_special(0);
        --size;
        return value;
    }

    long long GetSize() {
        return a.size();
    }

    long long GetCount(){
        return count;
    }

    void create_res(){
        for (long long i = a.size() - 1; i >= 0; --i) {
            siftDown_special(i);
        }
        while(size){
            std::tuple<long long, long long, long long> tmp = pop_special();
            for (int i = 0; i < std::get<2>(tmp)-1; ++i){
                res.push_back(std::get<1>(tmp));
            }
        }

    }

    void print(){
        std::cout << res.size() << "\n";
        for (long long i : res){
            std::cout << i << " ";
        }
    }
};

int main() {
    long long n;
    std::cin >> n;

    std::vector<std::tuple<long long, long long,long long>> primes;
    primes.resize(n);

    primes = eratosfen(7000000, n);

    Heap test(primes);

    while (test.GetCount() != n) {
        std::tuple<long long, long long,long long> tmp = test.pop();
        std::get<0>(tmp) = std::get<0>(tmp) * std::get<0>(tmp);
        test.push(tmp);
    }
    test.create_res();
    test.print();
    return 0;
}