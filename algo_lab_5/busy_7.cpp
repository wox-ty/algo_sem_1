#include <iostream>

struct Node {
    Node *left;
    Node *right;
    Node *parent;
    long long data;
    long long sum;
    long long max;
    long long min;

    Node () : left(nullptr), right(nullptr), parent(nullptr), data(0), sum(0), max(0), min(0) {}

    explicit Node (long long val) : left(nullptr), right(nullptr), parent(nullptr), data(val), sum(0), max(0), min(0) {}
};

long long max_sum = 0;

long long cnt(Node *cur_node) {
    if (cur_node == nullptr) {
        return 0;
    }

    long long left_cnt = cnt(cur_node->left);
    long long right_cnt = cnt(cur_node->right);

    if (left_cnt != -1 && right_cnt != -1) {
        if (cur_node->left == nullptr && cur_node->right == nullptr) {
            cur_node->min = cur_node->data;
            cur_node->max = cur_node->data;
            cur_node->sum = cur_node->data;
            if (cur_node->sum > max_sum){
                max_sum = cur_node->sum;
            }
            return cur_node->sum;
        }

        if (cur_node->left == nullptr){
            if (cur_node->right->min >= cur_node->data) {
                cur_node->min = cur_node->data;
                cur_node->max = cur_node->right->max;
                cur_node->sum = right_cnt + cur_node->data;
                if (cur_node->sum > max_sum){
                    max_sum = cur_node->sum;
                }
                return cur_node->sum;
            }
            return -1;
        }

        if (cur_node->right == nullptr){
            if (cur_node->left->max <= cur_node->data) {
                cur_node->max = cur_node->data;
                cur_node->min = cur_node->left->min;
                cur_node->sum = left_cnt + cur_node->data;
                if (cur_node->sum > max_sum){
                    max_sum = cur_node->sum;
                }
                return cur_node->sum;
            }
            return -1;
        }

        if (cur_node->left->max <= cur_node->data && cur_node->right->min >= cur_node->data){
            cur_node->min = cur_node->left->max;
            cur_node->max = cur_node->right->min;
            cur_node->sum = left_cnt + right_cnt + cur_node->data;
            if (cur_node->sum > max_sum){
                max_sum = cur_node->sum;
            }
            return cur_node->sum;
        }
    }
    return -1;
}

long long count(Node *root) {
    return cnt(root);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    char input;

    long long root_val;
    std::cin >> root_val;
    Node *cur_node = new Node(root_val);

    Node *root = cur_node;

    long long val;

    while (std::cin >> input){
        if (input == 's'){
            break;
        }
        if (input == 'l'){
            std::cin >> val;
            cur_node->left = new Node(val);
            cur_node->left->parent = cur_node;
            cur_node = cur_node->left;
        }
        else if (input == 'r'){
            std::cin >> val;
            cur_node->right = new Node(val);
            cur_node->right->parent = cur_node;
            cur_node = cur_node->right;
        }
        else if (input == 'u'){
            if (cur_node->parent != nullptr) {
                cur_node = cur_node->parent;
            }
        }
    }

    count(root);

    std::cout << max_sum;

    return 0;
}
/*
6 l 3 l 2 l 1 u u r 4 u u r 10 l 7 r 8 u u r 12
ans: 53

4 l 1
ans: 5

4 r 5
ans: 9

4 r 5 r 6
ans: 15

4 r 5 r 6 u u l 7 s
ans: 11

20 l -20 l 3 l 1 u u r 6 r 7 r 9 u u u u r 8 r 5 r 1000 l 12 u r 2
ans: 22

20 l -20 l 3 l 1 u u r 6 r 7 l 6 u r 9 u u u u r 8 r 5 r 1000 l 12 u r 2
ans: 28

20 l -20 l 3 l 1 u u r 6 r 7 l 6 u r 9 u u u u r 8 r 5 r 1000 l 12 u r 2 l 0 l -10 u r 1 u u r 3 r 4
ans: 28

20 l -20 l 3 l 1 u u r 6 r 7 l 6 u r 9 u u u u r 8 r 5 r 1000 l 12 u r 2 l 0 l -10 u r 1 u u r 3 r 100
ans: 103

100 r 110 l 108 u r 120 l 110 u r 130 l 170 u r 140
ans: 170

100 r 110 l 108 u r 120 l 110 u r 130 l 170 l 10 u r 180 u u r 140
ans: 360

100 l 90 r 95 u l 80 r 90 u l 70 l 60 u r 140
ans: 270

100 l 90 r 95 u l 80 r 90 u l 70 l 60 u r 140 l 20 u r 150
ans: 310

*/