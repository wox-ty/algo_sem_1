#include "iostream"
#include "string"
#include "vector"


struct Node {
    Node *left;
    Node *right;
    std::string data;
    long long height;
    long long balance;
    bool first;
    bool second;
    bool third;


    Node(){
        left = nullptr;
        right = nullptr;
        data = "";
        height = 0;
        balance = 0;
        first = false;
        second = false;
        third = false;
    };

    explicit Node(std::string val) {
        left = nullptr;
        right = nullptr;
        data = val;
        height = 0;
        balance = 0;
        first = false;
        second = false;
        third = false;
    };
};


class BSTree {
public:
    Node *root = nullptr;
private:
    Node *add_rec(Node *cur_node, const std::string& val, long long person) {
        if (cur_node == nullptr) {
            Node *tmp = new Node(val);
            if (person == 1) {
                tmp->first = true;
            }
            if (person == 2) {
                tmp->second = true;
            }
            if (person == 3) {
                tmp->third = true;
            }
            return tmp;
        } else if (val < cur_node->data) {
            cur_node->left = add_rec(cur_node->left, val, person);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val, person);
        } else if (val == cur_node->data) {
            if (person == 2) {
                cur_node->second = true;
            }
            if (person == 3) {
                cur_node->third = true;
            }
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

    void decrese_rec(Node *cur_node, long long &decr, long long person) {
        if (cur_node == nullptr) {
            return;
        }

        if (person == 1) {
            if (cur_node->first) {
                if (cur_node->second && cur_node->third) {
                    decr += 3;
                } else if (cur_node->second || cur_node->third) {
                    decr += 2;
                }
            }
        }
        if (person == 2) {
            if (cur_node->second) {
                if (cur_node->first && cur_node->third) {
                    decr += 3;
                } else if (cur_node->first || cur_node->third) {
                    decr += 2;
                }
            }
        }
        if (person == 3) {
            if (cur_node->third) {
                if (cur_node->second && cur_node->first) {
                    decr += 3;
                } else if (cur_node->second || cur_node->first) {
                    decr += 2;
                }
            }
        }

        if (cur_node->left) {
            decrese_rec(cur_node->left, decr, person);
        }
        if (cur_node->right) {
            decrese_rec(cur_node->right, decr, person);
        }
    }

public:

    BSTree() = default;

    void add(const std::string& val, long long num) {
        root = add_rec(root, val, num);
    }

    long long decrese(long long num) {
        long long dec = 0;
        decrese_rec(root, dec, num);
        return dec;
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

    long long sums[3];
    for (long long i = 0; i < 3; ++i) {
        sums[i] = 3 * n;
    }


    for (long long i = 1; i < 4; ++i) {
        for (long long j = 0; j < n; ++j) {
            std::cin >> task_name;
            tree.add(task_name, i);
        }
    }

    for (long long j = 1; j < 4; ++j) {
        sums[j - 1] -= tree.decrese(j);
    }

    std::cout << sums[0] << " " << sums[1] << " " << sums[2];

    return 0;
}
/*
3
fir sec thi
thi fir sec
aaa sec bbb
ans: 2 2 6

7
111 222 333 444 555 666 777
111 222 333 999 555 666 777
000 111 222 333 999 777 666
ans: 4 2 4

*/