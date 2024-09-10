#include "iostream"

class Linked_list {
public:

    void push_back(long long data) {
        Node *tmp = new Node();
        tmp->data = data;

        tmp->prev = tail;
        if (tail != nullptr){
            tail->next = tmp;
        }
        if (head == nullptr){
            head = tmp;
        }
        tail = tmp;

        ++Size;
    }

    void Push_index(long long index){
        tail->index = index;
    }

    std::pair<long long,long long> pop_back() {
        if(tail != nullptr){
            long long data = tail->data;
            long long idx = tail->index;
            Node *tmp = tail->prev;

            if (tmp != nullptr) {
                tmp->next = nullptr;
            } else {
                head = nullptr;
            }


            --Size;
            delete tail;
            tail = tmp;
            return std::make_pair(data, idx);
        }
    }

    void push_front(long long data) {
        Node *tmp = new Node();
        tmp->data = data;

        tmp->next = head;
        if (head != nullptr){
            head->prev = tmp;
        }
        if (tail == nullptr){
            tail = tmp;
        }
        head = tmp;

        ++Size;
    }

    long long pop_front() {
        if (head != nullptr){
            long long data = head->data;
            Node *tmp = head->next;

            if (tmp != nullptr) {
                tmp->prev = nullptr;
            } else {
                tail = nullptr;
            }


            --Size;
            delete head;
            head = tmp;
            return data;
        }
    }

    long long ShowBack(){
        long long datal = tail-> data;
        return datal;
    }

    long long GetSize() {
        return Size;
    }

private:

    struct Node {
        Node *next = nullptr;
        Node *prev = nullptr;
        long long data{};
        long long index{};
    };
    Node *head = nullptr;
    Node *tail = nullptr;
//    long long data = 0;
//    long long index = 0;

    long long Size = 0;
};

struct Stack {
private:
    Linked_list Planks;

public:
    void push(long long data, long long index) {
        Planks.push_back(data);
        Planks.Push_index(index);
    }

    std::pair<long long,long long> pop() {
        return Planks.pop_back();
    }

    long long Top(){
        return Planks.ShowBack();
    }
    long long GetSize(){
        return Planks.GetSize();
    }
};

int main(){
    long long n;
    std::cin >> n;

    Stack test;

    long long cur_Plank_len;
    long long idx = 0;
    long long cur_S = 0, Max_S = 0;
    long long min_idx;

    test.push(0, -1);

    for (int i = 0; i < n; ++i){
        cur_S = 0;
        std::cin >> cur_Plank_len;

        if (test.Top() < cur_Plank_len){
            test.push(cur_Plank_len, idx);
            ++idx;
            continue;
        }

        if (test.Top() >= cur_Plank_len){
            while (test.Top() >= cur_Plank_len){
                std::pair<long long,long long> x = test.pop();
                cur_S = x.first * (idx - x.second);
                min_idx = x.second;
                if (Max_S < cur_S){
                    Max_S = cur_S;
                }
            }
            test.push(cur_Plank_len, min_idx);
            ++idx;
        }

    }
    long long r = test.GetSize();
    for (int i = 0; i < r;++i){
        std::pair<long long,long long> a = test.pop();
        cur_S = a.first * (n-a.second);
        if (Max_S < cur_S){
            Max_S = cur_S;
        }
    }

    std::cout << Max_S;

    return 0;
}
/*
5
1 2 3 4 5
 *
6
2 1 5 6 2 3

6
1 2 3 3 2 1
*/