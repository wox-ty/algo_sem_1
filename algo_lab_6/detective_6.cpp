#include "iostream"
#include "vector"


struct Node {
    Node *left;
    Node *right;
    long data;
    long height;
    long balance;


    Node() = default;

    explicit Node(long val) {
        left = nullptr;
        right = nullptr;
        data = val;
        height = 1;
        balance = 0;
    };
};


class BSTree {
public:
    Node *root = nullptr;
private:
    Node *add_rec(Node *cur_node, long val) {
        if (cur_node == nullptr) {
            return new Node(val);
        } else if (val < cur_node->data) {
            cur_node->left = add_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val);
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

    Node *remove_rec(Node *cur_node, long val) {
        if (cur_node == nullptr) {
            return cur_node;
        }

        if (val < cur_node->data) {
            cur_node->left = remove_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = remove_rec(cur_node->right, val);
        } else if (cur_node->left != nullptr && cur_node->right != nullptr) {
            Node *tmp_l = cur_node->left;
            Node *tmp_r = cur_node->right;

            Node *min = prev(cur_node->data);
            min->left = remove_rec(tmp_l, min->data);
            min->right = tmp_r;

            delete cur_node;
            return Balance(min);
        } else {
            Node *tmp_l = cur_node->left;
            Node *tmp_r = cur_node->right;

            if (tmp_l != nullptr) {
                cur_node = tmp_l;
            } else if (tmp_r != nullptr) {
                cur_node = tmp_r;
            } else {
                cur_node = nullptr;
            }
        }
        return Balance(cur_node);
    }

    long fix_heights_rec(Node *cur_node){
        cur_node->height = std::max((cur_node->left ? cur_node->left->height : 0),
                                    (cur_node->right ? cur_node->right->height : 0)) + 1;
        cur_node->balance = ((cur_node->right ? cur_node->right->height : 0) -
                             (cur_node->left ? cur_node->left->height : 0));
        return cur_node->height;
    }

    Node *find_recursive(Node *cur_node, long val) {
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

    void add(long val) {
        root = add_rec(root, val);
    }

    bool find(long val) {
        Node *tmp = find_recursive(root, val);
        if (tmp) {
            return true;
        } else {
            return false;
        }
    }

    void remove(long val) {
        root = remove_rec(root, val);
    }

    Node *prev(long val) {
        Node *cur_node = root;
        Node *child = nullptr;
        while (cur_node != nullptr) {
            if (cur_node->data >= val) {
                cur_node = cur_node->left;
            } else if (cur_node->data < val) {
                child = cur_node;
                cur_node = cur_node->right;
            }
        }
        return child;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long n;
    std::cin >> n;
    char Operation;
    BSTree tree;
    long value;
    for (long i = 0; i < n; ++i) {
        std::cin >> Operation >> value;
        if (Operation == 'A') {
            tree.add(value);
            std::cout << (tree.root ? tree.root->balance : 0) << "\n";
        } else if (Operation == 'D') {
            tree.remove(value);
            std::cout << (tree.root ? tree.root->balance : 0) << "\n";
        } else if (Operation == 'C') {
            if (tree.find(value)) {
                std::cout << 'Y' << "\n";
            } else {
                std::cout << 'N' << "\n";
            }
        }
    }


    return 0;
}
/*
8
A 3
D 3
A 4
D 4
A 5
C 5
D 5
C 5

7
A 3
A 4
A 6
A 5
A 7
D 6
D 3



*/