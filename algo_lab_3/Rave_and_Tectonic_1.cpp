#include "iostream"

class Linked_list {
public:

    void push_back(int data) {
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

    int pop_back() {
        if(tail != nullptr){
            int data = tail->data;
            Node *tmp = tail->prev;

            if (tmp != nullptr) {
                tmp->next = nullptr;
            } else {
                head = nullptr;
            }


            --Size;
            delete tail;
            tail = tmp;
            return data;
        }
    }

    void push_front(int data) {
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

    int pop_front() {
        if (head != nullptr){
            int data = head->data;
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

    int GetSize() {
        return Size;
    }

private:

    struct Node {
        Node *next = nullptr;
        Node *prev = nullptr;
        int data{};
    };
    Node *head = nullptr;
    Node *tail = nullptr;

    int Size = 0;
};

struct Stack {
private:
    Linked_list History;
    Linked_list Deleted;

public:
    void push(int data) {
        History.push_back(data);
    }

    void pop() {
        Deleted.push_back(History.pop_back());
    }

    void print() {
        while (Deleted.GetSize()) {
            std::cout << Deleted.pop_front() << "\n";
        }
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    Stack test;
    char operation;
    int x;

    for (int i = 0; i < n; ++i) {
        std::cin >> operation;
        if (operation == '+') {
            std::cin >> x;
            test.push(x);
        } else if (operation == '-') {
            test.pop();
        }
    }

    test.print();

    return 0;
}
/*
6
+ 1
-
+ 10
-
+ 100
-
*/