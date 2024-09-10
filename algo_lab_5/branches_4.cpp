#include "iostream"
#include "string"
#include "vector"
#include "queue"


struct Node {
    Node *left;
    Node *right;
    long data;

    Node() = default;

    explicit Node(long val) {
        left = nullptr;
        right = nullptr;
        data = val;
    };
};


class BSTree {
private:
    Node *root = nullptr;

    Node *create_rec(std::vector<long> &a, long start, long end) {
        if (start > end) {
            return nullptr;
        }

        long mid = start + (end - start) / 2;
        Node *cur_node = new Node(a[mid]);

        cur_node->left = create_rec(a, start, mid - 1);

        cur_node->right = create_rec(a, mid + 1, end);


        return cur_node;
    }

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

    void Rightest(Node *cur_node) {
        if (cur_node == nullptr) {
            return;
        }

        std::queue<Node *> que;
        que.push(cur_node);

        while (!que.empty()) {
            long size = que.size();
            for (long i = 0; i < size; i++) {
                Node *tmp = que.front();
                que.pop();

                if (i == size - 1) {
                    std::cout << tmp->data << " ";
                }

                if (tmp->left != nullptr) {
                    que.push(tmp->left);
                }
                if (tmp->right != nullptr) {
                    que.push(tmp->right);
                }
            }
        }
    }

    Node *create_tree_rec(std::vector<long> &arr, long &i, long min, long max) {
        if (i >= arr.size()) {
            return nullptr;
        }

        if (arr[i] < min || arr[i] > max) {
            return nullptr;
        }

        Node *cur_node = new Node(arr[i]);
        ++i;

        if (i < arr.size() && arr[i] < cur_node->data && arr[i] >= min) {
            cur_node->left = create_tree_rec(arr, i, min, cur_node->data);
        }
        if (i < arr.size() && arr[i] >= cur_node->data && arr[i] <= max) {
            cur_node->right = create_tree_rec(arr, i, cur_node->data, max);
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

    void add(Node *address, long val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        } else {
            add_rec(address, val);
        }
    }

    BSTree(std::vector<long> &arr, bool sorted) {
        if (!sorted) {
            for (long i: arr) {
                add(i);
            }
        } else {
            root = create_rec(arr, 0, arr.size() - 1);
        }
    };

    bool find(long val) {
        return find_recursive(root, val);
    }

    void remove(long val) {
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

    void myord() {
        Rightest(root);
    }

    Node *next(long val) {
        Node *cur_node = root;
        Node *child = nullptr;
        while (cur_node != nullptr) {
            if (cur_node->data > val) {
                child = cur_node;
                cur_node = cur_node->left;
            } else if (cur_node->data < val) {
                cur_node = cur_node->right;
            }
        }

        return child;
    }

    Node *prev(long val) {
        Node *cur_node = root;
        Node *child = nullptr;
        while (cur_node != nullptr) {
            if (cur_node->data > val) {
                cur_node = cur_node->left;
            } else if (cur_node->data < val) {
                child = cur_node;
                cur_node = cur_node->right;
            }
        }

        return child;
    }

    void create_tree_from_pre(std::vector<long> &arr) {
        long IDX = 0;
        root = create_tree_rec(arr, IDX, LONG_MIN, LONG_MAX);
    }
};

BSTree preord_to_tree(std::vector<long> &arr) {
    BSTree tmp;
    Node *address;
    for (long i = 0; i < arr.size(); ++i) {
        if (i == 0) {
            tmp.add(arr[i]);
        } else if (arr[i - 1] > arr[i]) {
            tmp.add(arr[i]);
        } else if (arr[i - 1] < arr[i]) {
            address = tmp.prev(arr[i]);
            tmp.add(address, arr[i]);
        }
    }

    return tmp;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    BSTree tree;
    long n;
    std::cin >> n;
    std::vector<long> test;
    test.resize(n);
    for (long i = 0; i < n; ++i) {
        std::cin >> test[i];
    }

    tree.create_tree_from_pre(test);
//    tree = preord_to_tree(test);
//    tree.preorder();
//    tree.myord();
//    std::cout << "\n";
//    tree.myord();
//    std::cout << "\n" << "\n";
//
    BSTree tree2;
    tree2.create_tree_from_pre(test);
    tree2.preorder();
    std::cout << "\n";
    tree2.myord();
    std::cout << "\n" << "\n";
    tree.preorder();
    std::cout << "\n";
    tree.myord();
    std::cout << "\n" << "\n";
    tree.inorder();
    std::cout << "\n" << "\n";

    return 0;
}
/*
12
40 25 10 3 17 32 30 38 78 50 78 93

11
40 25 10 3 17 32 30 38 78 50 93

5
40 25 10 32 78

10
5 4 3 1 9 8 6 7 15 10

---
5
-2 -4 -15 -5 -1
---

---
10
5 4 3 -30 0 1 2 15 8 30
---

5
4 5 6 7 8

5
10 9 8 7 6
*/