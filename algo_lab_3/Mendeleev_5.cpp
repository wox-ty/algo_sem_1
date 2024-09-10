#include "iostream"
#include "string"


class Linked_list {
public:

    void push_back(char data) {
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

        tail->next = tmp;
        tail = tmp;

        ++Size;
    }

    char pop_back() {
        char data = tail->data;
        tail = tail->prev;
        --Size;

        return data;
    }

    void push_front(char data) {
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

    char pop_front() {
        char data = head->data;
        head = head->next;
        --Size;

        return data;
    }

    int GetSize() {
        return Size;
    }

private:

    struct Node {
        Node *next = nullptr;
        Node *prev = nullptr;
        char data{};
    };
    Node *head{};
    Node *tail{};

    int Size = 0;
};


struct Stack {
private:
    Linked_list History;
    Linked_list Deleted;

public:
    void push(char data) {
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
    char a;

    Stack test;

    while (true) {
        std::cin >> a;
        if (a == ' ') {
            break;
        }
        test.push(a);
    }

    test.print();


    return 0;
}