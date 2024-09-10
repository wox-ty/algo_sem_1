#include "iostream"

class Linked_list {
public:

    void push_back(int data) {
        if (head == nullptr) {
            head = new Node();
            head->data = data;

            tail = head;

            head->next = tail;
            tail->prev = head;

            ++Size;

            return;
        }

        Node *tmp = new Node();
        tmp->data = data;
        tmp->prev = tail;
        tmp->check = tail->check;

        if (tmp->check){
            MaxLoop = Loop;
            Loop = 0;
        }
        else{
            ++Loop;
            tmp->check = true;
        }

        tail->next = tmp;
        tail = tmp;

        ++Size;
    }

    int pop_back() {
        int data = tail->data;
        tail = tail->prev;
        --Size;

        return data;
    }

    void push_front(int data) {
        if (head == nullptr) {
            push_back(data);
            return;
        }

        Node *tmp = new Node();
        tmp->data = data;
        tmp->next = head;

        head->prev = tmp;
        head = tmp;

        ++Size;
    }

    int pop_front() {
        int data = head->data;
        head = head->next;
        --Size;

        return data;
    }

    int GetSize() {
        return Size;
    }

    int GetLoopSize(){
        if (MaxLoop == 0){
            return -1;
        }
        return MaxLoop;
    }

private:

    struct Node {
        Node *next = nullptr;
        Node *prev = nullptr;
        int data{};
        bool check = false;
    };
    Node *head{};
    Node *tail{};

    int MaxLoop = 0;
    int Loop = 0;
    int Size = 0;
};

int main(){
    int n;
    std::cin >> n;

    Linked_list test;

    int a;
    for (int i = 0; i < n; ++i){
        std::cin >> a;
        test.push_back(a);
    }

    std::cout << test.GetLoopSize();

    return 0;
}