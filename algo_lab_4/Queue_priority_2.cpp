#include "iostream"
#include "string"
#include "vector"


class Heap {
private:
    std::vector<int> a;

public:

    Heap() = default;

    void siftUp(int index) {
        while (index != 0 && a[index] < a[(index - 1) / 2]) {

            std::swap(a[index], a[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void siftDown(int index) {
        while (2 * index + 1 < a.size()) {
            int minChild = 2 * index + 1;
            if (minChild + 1 < a.size() && a[minChild] > a[minChild + 1]) {
                ++minChild;
            }

            if (a[index] <= a[minChild]) {
                break;
            }

            std::swap(a[index], a[minChild]);
            index = minChild;
        }
    }

    Heap(std::vector<int> &values) {
        a = values;
        for (int i = a.size() - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    void push(int value) {
        a.push_back(value);
        siftUp(a.size() - 1);
    }

    int pop() {
        if (a.empty()){
            return -10101;
        }
        int value = a[0];
        a[0] = a[a.size() - 1];
        a.pop_back();
        siftDown(0);

        return value;
    }

    void decrease_key(int replaced_value, int value){
        int idx = 0;
        while(a[idx] != replaced_value){
            ++idx;
        }
        a[idx] = value;
        siftUp(idx);
    }

    int GetSize(){
        return a.size();
    }
};

Heap merge(Heap k, Heap m){
    Heap *res = new Heap();
    int size1 = k.GetSize();
    int size2 = m.GetSize();
    for(int i = 0; i < size1; ++i){
        res->push(k.pop());
    }
    for(int j = 0; j < size2; ++j){
        res->push(m.pop());
    }
    res->siftDown(0);

    return *res;
}

int main(){
    std::string operation;
    int k, m, x, y;
    std::vector<Heap> test;
    std::vector<int> res;

    while (std::cin >> operation){
        if (operation == "create"){
            Heap *tmp = new Heap();
            test.push_back(*tmp);
        }
        else if (operation == "insert"){
            std::cin >> k >> x;
            test[k].push(x);
        }
        else if (operation == "extract-min"){
            std::cin >> k;
            res.push_back(test[k].pop());
        }
        else if (operation == "merge"){
            std::cin >> k >> m;
            test.push_back(merge(test[k], test[m]));
        }
        else if (operation == "decrease-key"){
            std::cin >> k >> x >> y;
            test[k].decrease_key(x,y);
        }
    }
    for (int re : res){
        if (re == -10101) {
            std::cout << '*' << "\n";
        }
        else{
            std::cout << re << "\n";
        }
    }
    return 0;
}