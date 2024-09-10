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
    Node *head{};
    Node *tail{};

    int Size = 0;
};

struct Deck {
private:
    Linked_list BAG;

public:
    void push(int data) {
        BAG.push_back(data);
    }

    int pop_front() {
        return BAG.pop_front();
    }

    int pop_back() {
        return BAG.pop_back();
    }

    int GetSize() {
        return BAG.GetSize();
    }

    void print() {
        while (BAG.GetSize()) {
            std::cout << BAG.pop_front() << " ";
        }
    }

};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    Deck test;
    int tmp;
    int trock, brock;
    int tmp1, tmp2;
    int sum;

    for (int i = 0; i < N; ++i) {
        std::cin >> tmp;
        if (test.GetSize() < M) {
            test.push(tmp);
        } else {
            trock = test.pop_back();
            brock = test.pop_front();

            if (trock <= tmp && trock <= brock) {
                tmp1 = std::max(tmp, brock);
                tmp2 = std::min(tmp, brock);
            } else if (tmp <= trock && tmp <= brock) {
                tmp1 = std::max(trock, brock);
                tmp2 = std::min(trock, brock);
            } else {
                tmp1 = std::max(tmp, trock);
                tmp2 = std::min(tmp, trock);
            }

            test.push(tmp2);
            test.push(tmp1);

        }
    }

    test.print();

    return 0;
}