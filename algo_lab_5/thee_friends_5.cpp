#include "iostream"
#include "vector"
#include "string"


struct Node {
    Node *left;
    Node *right;
    std::string data;
    long long counter;

    Node() = default;

    explicit Node(std::string val) {
        left = nullptr;
        right = nullptr;
        data = val;
        counter = 1;
    };
};


class BSTree {
private:
    Node *root = nullptr;

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
        return cur_node;
    }

    Node *remove_rec(Node *cur_node, std::string val) {
        if (cur_node == nullptr) {
            return cur_node;
        }

        if (val < cur_node->data) {
            cur_node->left = remove_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = remove_rec(cur_node->right, val);
        } else if (cur_node->left != nullptr && cur_node->right != nullptr) {
            cur_node->data = findMin(cur_node->right)->data;
            cur_node->right = remove_rec(cur_node->right, cur_node->data);
        } else {
            if (cur_node->left != nullptr) {
                cur_node = cur_node->left;
            } else if (cur_node->right != nullptr) {
                cur_node = cur_node->right;
            } else {
                cur_node = nullptr;
            }
        }
        return cur_node;
    }

    void preorder_rec(Node *node) {
        if (node != nullptr) {
            std::cout << node->data << " ";
            preorder_rec(node->left);
            preorder_rec(node->right);
        }
    }

    void postorder_rec(Node *node) {
        if (node != nullptr) {
            postorder_rec(node->left);
            postorder_rec(node->right);
            std::cout << node->data << " ";
        }
    }

    void inorder_rec(Node *node) {
        if (node != nullptr) {
            inorder_rec(node->left);
            std::cout << node->data << " ";
            inorder_rec(node->right);
        }
    }

    Node *findMin(Node *cur_node) {
        if (cur_node->left == nullptr) {
            return cur_node;
        }
        return findMin(cur_node->left);
    }

    Node *findMax(Node *cur_node) {
        if (cur_node->right == nullptr) {
            return cur_node;
        }
        return findMin(cur_node->right);
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

public:

    BSTree() = default;

    void add(std::string val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        } else {
            add_rec(root, val);
        }
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
//        return tmp ? find_recursive(root, val)->counter : 0;
    }

    void remove(std::string val) {
        root = remove_rec(root, val);
    }

    void preorder() {
        preorder_rec(root);
    }

    void postorder() {
        postorder_rec(root);
    }

    void inorder() {
        inorder_rec(root);
    }

    Node *next(std::string val) {
        Node *cur_node = root;
        Node *child = nullptr;
        while (cur_node != nullptr) {
            if (cur_node->data > val) {
                child = cur_node;
                cur_node = cur_node->left;
            } else if (cur_node->data <= val) {
                cur_node = cur_node->right;
            }
        }
        return child;
    }

    Node *prev(std::string val) {
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
    long long N;
    std::cin >> N;

    std::string task_name;

    BSTree tree;

    std::string all[3][N];

    for (long long i = 0; i < 3; ++i) {
        for (long long j = 0; j < N; ++j) {
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
        for (long long j = 0; j < N; ++j) {
            sums[i] += tree.find(all[i][j]);
        }
    }

    std::cout << sums[0] << " " << sums[1] << " " << sums[2];
    return 0;
}
/*
7
111 222 333 444 555 666 777
111 222 333 999 555 666 777
000 111 222 333 999 777 666

*/