#include <queue>
#include "iostream"
#include "string"
#include "vector"


struct Node {
    Node *left;
    Node *right;
    long long data;
    long long left_idx;
    long long right_idx;
    long long height;
    long long balance;
    long long id;

    Node() = default;

    explicit Node(long long val) {
        left = nullptr;
        right = nullptr;
        data = val;
        left_idx = 0;
        right_idx = 0;
        height = 0;
        balance = 0;
        id = 0;
    };

    explicit Node(long long val, long long lefty, long long righty) {
        left = nullptr;
        right = nullptr;
        data = val;
        left_idx = lefty;
        right_idx = righty;
        height = 0;
        balance = 0;
        id = 0;
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
        return cur_node;
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

    void inorder_rec(Node *node) {
        if (node != nullptr) {
            inorder_rec(node->left);
            std::cout << node->data << " ";
            inorder_rec(node->right);
        }
    }

    void widthorder_rec(Node* cur_node, std::vector<long long> &arr) {
        if (cur_node == nullptr) {
            return;
        }

        std::queue<Node*> que;
        que.push(cur_node);

        while (!que.empty()) {
            Node* current = que.front();
            que.pop();
            arr[current->id] = current->balance;

            if (current->left != NULL) {
                que.push(current->left);
            }
            if (current->right != NULL) {
                que.push(current->right);
            }
        }
    }

    long long set_heights_rec(Node *cur_node) {
        if (cur_node == nullptr) {
            return 0;
        }
        cur_node->height = std::max((cur_node->left ? set_heights_rec(cur_node->left) : 0), (cur_node->right ? set_heights_rec(cur_node->right) : 0)) + 1;

        cur_node->balance = ((cur_node->right ? cur_node->right->height : 0) - (cur_node->left ? cur_node->left->height : 0));

        return cur_node->height;
    }

    Node *findMin(Node *cur_node) {
        if (cur_node->left == nullptr) {
            return cur_node;
        }
        return findMin(cur_node->left);
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

    Node *Build_BST_rec(std::vector<Node *> &arr, long long idx) {
        Node *cur_node = arr[idx];
        cur_node->id = idx;
        if (cur_node->left_idx) {
            cur_node->left = Build_BST_rec(arr, cur_node->left_idx);
        }
        if (cur_node->right_idx) {
            cur_node->right = Build_BST_rec(arr, cur_node->right_idx);
        }

        return cur_node;
    }

public:

    BSTree() = default;

    void add(long val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        } else {
            add_rec(root, val);
        }
    }

    bool find(long val) {
        return find_recursive(root, val);
    }

    void remove(long val) {
        root = remove_rec(root, val);
    }

    void inorder() {
        inorder_rec(root);
    }

    void build(std::vector<Node *> &arr) {
        root = Build_BST_rec(arr, 1);
    }

    void check_balance(std::vector<long long> &arr) {
        widthorder_rec(root, arr);
    }

    void set_heights() {
        set_heights_rec(root);
    }
};


int main() {
    long long n;
    std::cin >> n;

    long long K, L, R;

    std::vector<Node *> all;
    all.push_back(new Node(0));

    BSTree tree;

    std::vector<long long> ans;

    for (long long i = 1; i < n + 1; ++i) {
        std::cin >> K >> L >> R;
        Node *tmp = new Node(K, L > 0 ? L : 0, R > 0 ? R : 0);
        all.push_back(tmp);
    }

    tree.build(all);

    //задать высоты
    tree.set_heights();

    //проверить баланс
    ans.resize(n+1);
    tree.check_balance(ans);

    for (int i = 1; i <= n; ++i){
        std::cout << ans[i] << "\n";
    }

//    all.clear();

    return 0;
}
/*
6
-2 0 2
8 4 3
9 0 0
3 5 6
0 0 0
6 0 0

2
1 0 2
5 0 0

5
4 5 2
5 0 3
7 4 0
6 0 0
1 0 0
выводит:
2
0
2
-1
0
должно:
2
2
-1
0
0



*/