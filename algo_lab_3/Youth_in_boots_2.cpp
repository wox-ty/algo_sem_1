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

struct Queue{

    Linked_list IN;
    Linked_list OUT;

    void push(int data){
        IN.push_back(data);
    }

    int pop(){
        int x = IN.pop_front();
        OUT.push_back(x);
        return x;
    }

    void print(){
        while (OUT.GetSize()){
            std::cout << OUT.pop_front() << "\n";
        }
    }

};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    Queue test;
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