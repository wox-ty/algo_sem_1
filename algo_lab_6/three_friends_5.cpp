#include "iostream"
#include "string"
#include "vector"


struct Node {
    Node *left;
    Node *right;
    std::string data;
    long long height;
    long long balance;
    long long counter;


    Node() = default;

    explicit Node(std::string val) {
        left = nullptr;
        right = nullptr;
        data = val;
        height = 0;
        balance = 0;
        counter = 1;
    };
};


class BSTree {
public:
    Node *root = nullptr;
private:
    Node *add_rec(Node *cur_node, std::string val) {
        if (cur_node == nullptr) {
            return new Node(val);
        } else if (val < cur_node->data) {
            cur_node->left = add_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val);
        } else if (val == cur_node->data) {
            cur_node->counter += 1;
        }
        return Balance(cur_node);
    }

    long set_height(Node* cur_node){
        if (cur_node == nullptr){
            return 0;
        }
        return cur_node->height;
    }

    long set_balance(Node* cur_node){
        if (cur_node == nullptr){
            return 0;
        }
        return (set_height(cur_node->right) - set_height(cur_node->left));
    }

    long fix_heights_rec(Node *cur_node){
        cur_node->height = std::max((cur_node->left ? cur_node->left->height : 0),
                                    (cur_node->right ? cur_node->right->height : 0)) + 1;
        cur_node->balance = ((cur_node->right ? cur_node->right->height : 0) -
                             (cur_node->left ? cur_node->left->height : 0));
        return cur_node->height;
    }

    Node *find_recursive(Node *cur_node, std::string val) {
        if (cur_node == nullptr || val == cur_node->data) {
            return cur_node;
        }
        if (val < cur_node->data) {
            return find_recursive(cur_node->left, val);
        } else if (val > cur_node->data) {
            return find_recursive(cur_node->right, val);
        }
    }

    Node *rotate_left(Node *cur_node) {
        Node *tmp = cur_node->right;
        cur_node->right = tmp->left;
        tmp->left = cur_node;
        fix_heights_rec(cur_node);
        fix_heights_rec(tmp);

        return tmp;
    }

    Node *rotate_right(Node *cur_node) {
        Node *tmp = cur_node->left;
        cur_node->left = tmp->right;
        tmp->right = cur_node;
        fix_heights_rec(cur_node);
        fix_heights_rec(tmp);

        return tmp;
    }

    Node *Balance(Node *cur_node) {
        if (cur_node) {
            cur_node->height = fix_heights_rec(cur_node);
            cur_node->balance = set_balance(cur_node);
            if (cur_node->balance == 2) {
                if (cur_node->right->balance < 0) {
                    cur_node->right = rotate_right(cur_node->right);
                }
                return rotate_left(cur_node);
            }
            if (cur_node->balance == -2) {
                if (cur_node->left->balance > 0) {
                    cur_node->left = rotate_left(cur_node->left);
                }
                return rotate_right(cur_node);
            }
        }
        return cur_node;
    }

public:

    BSTree() = default;

    void add(std::string val) {
        root = add_rec(root, val);
    }

    long long find(std::string val) {
        Node *tmp = find_recursive(root, val);
        if (tmp->counter == 1) {
            return 3;
        } else if (tmp->counter == 2) {
            return 1;
        } else if (tmp->counter == 3) {
            return 0;
        } else {
            return 0;
        }
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n;
    std::cin >> n;

    BSTree tree;

    std::string task_name;

    std::string all[3][n];

    for (long long i = 0; i < 3; ++i) {
        for (long long j = 0; j < n; ++j) {

            std::cin >> task_name;
            all[i][j] = task_name;
            tree.add(task_name);
        }
    }

    long long sums[3];
    for (long long i = 0; i < 3; ++i) {
        sums[i] = 0;
    }

    for (long long i = 0; i < 3; ++i) {
        for (long long j = 0; j < n; ++j) {
            sums[i] += tree.find(all[i][j]);
        }
    }

    std::cout << sums[0] << " " << sums[1] << " " << sums[2];

    return 0;
}
/*
3
fir sec thi
thi fir sec
aaa sec bbb

7
111 222 333 444 555 666 777
111 222 333 999 555 666 777
000 111 222 333 999 777 666
ans: 4 2 4

*/