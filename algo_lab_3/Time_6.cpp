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

    int ShowBack(){
        int data = tail->data;

        return data;
    }

    int ShowFront(){
        long  long data = head->data;

        return data;
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

    void add_day(int day){
        head->day = day;
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

    void Print(){
        while (Size){
            std::cout << pop_back() <<  " ";
        }
    }

    void Print_days(){
        while(Size) {
            std::cout << head->day << " ";
            pop_front();
        }
    }

    int GetDay(){
        int x = head->day;
        return x;
    }


private:

    struct Node {
        Node *next = nullptr;
        Node *prev = nullptr;
        int data{};
        int day{};
    };
    Node *head{};
    Node *tail{};

    int Size = 0;
};

struct Deck{

    Linked_list IN;
    int Size = 0;

    void push_front(int data){
        IN.push_front(data);
        ++Size;
    }

    int pop_fornt(){
        int x = IN.pop_front();
        --Size;
        return x;
    }

    int Start(){
        int x = IN.ShowFront();
        return x;
    }

    void print(){
        while (IN.GetSize()){
            std::cout << IN.pop_back() << " ";
            --Size;
        }
    }

    int GetSize(){
        return Size;
    }

    void dayd(int day){
        IN.add_day(day);
    }

    void Print_day(){
        IN.Print_days();
    }


};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int difficulty[n];
    for (int i = 0; i < n; ++i){
        std::cin >> difficulty[i];
    }

    Deck test;
    Linked_list ans_ind;
    int counter;
    Linked_list copy;


    for (int j = n-1; j > -1; --j){
        counter = 1;

        while(test.GetSize() != 0){
            if (test.Start() <= difficulty[j]){
                test.pop_fornt();
                counter += copy.GetDay();
                copy.pop_front();
            }
            else{
                break;
            }
        }


        if (test.GetSize() != 0){
            ans_ind.push_back(counter);
        }
        else{
            counter = -1;
            ans_ind.push_back(counter);
        }

        copy.push_front(difficulty[j]);
        copy.add_day(counter);

        test.push_front(difficulty[j]);
        test.dayd(counter);
    }

    ans_ind.Print();

    return 0;
}