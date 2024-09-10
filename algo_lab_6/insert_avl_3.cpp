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
    Node *add_rec(Node *cur_node, long long val) {
        if (cur_node == nullptr) {
            return new Node(val);
        } else if (val < cur_node->data) {
            cur_node->left = add_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val);
        }
        return Balance(cur_node);
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

    void widthorder_rec(Node* cur_node) {
        if (cur_node == nullptr) {
            return;
        }

        std::queue<Node*> que;
        que.push(cur_node);

        while (!que.empty()) {
            Node* current = que.front();
            que.pop();
            std::cout << current->data << " " << current->left_idx << " " << current->right_idx;

            if (current->left != NULL) {
                que.push(current->left);
            }
            if (current->right != NULL) {
                que.push(current->right);
            }
//            if (que.size() != 0){
//                std::cout << "\n";
//            }
            std::cout << "\n";
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

        return Balance(cur_node);
    }

    Node *rotate_left(Node *cur_node) {
        Node *tmp = cur_node->right;
        cur_node->right = tmp->left;
        tmp->left = cur_node;
        set_heights_rec(cur_node);
        set_heights_rec(tmp);

        return tmp;
    }

    Node *rotate_right(Node *cur_node) {
        Node *tmp = cur_node->left;
        cur_node->left = tmp->right;
        tmp->right = cur_node;
        set_heights_rec(cur_node);
        set_heights_rec(tmp);

        return tmp;
    }

    Node *Balance(Node *cur_node) {
        set_heights_rec(cur_node);
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
        return cur_node;
    }

    void fix_rec(Node *cur_node){
        if (cur_node->left){
            fix_rec(cur_node->left);
        }
        if (cur_node->right){
            fix_rec(cur_node->right);
        }
        cur_node = Balance(cur_node);
    }

    void width_set_rec(Node* cur_node) {
        if (cur_node == nullptr) {
            return;
        }

        std::queue<Node*> que;
        que.push(cur_node);
        long long counter = 1;
        while (!que.empty()) {
            Node* current = que.front();
            que.pop();

            current->id = counter;
            if (current->left != NULL) {
                que.push(current->left);
            }
            if (current->right != NULL) {
                que.push(current->right);
            }

            ++counter;
        }
    }

    void set_left_right_rec(Node *cur_node){
        if (cur_node) {
            if (cur_node->left){
                cur_node->left_idx = cur_node->left->id;
                set_left_right_rec(cur_node->left);
            }
            else {
                cur_node->left_idx = 0;
            }
            if (cur_node->right){
                cur_node->right_idx = cur_node->right->id;
                set_left_right_rec(cur_node->right);
            }
            else {
                cur_node->right_idx = 0;
            }
        }
    }

public:

    BSTree() = default;

    void add(long long val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        } else {
            root = add_rec(root, val);
        }
    }

    void remove(long val) {
        root = remove_rec(root, val);
    }

    void inorder() {
        inorder_rec(root);
    }

    void build(std::vector<Node *> &arr) {
        if (arr.size() != 1) {
            root = Build_BST_rec(arr, 1);
        }
    }

    void set_heights() {
        set_heights_rec(root);
    }

    void widthorder(){
        widthorder_rec(root);
    }

    void set_rec(){
        width_set_rec(root);
        set_left_right_rec(root);
    }

    void fix(){
        fix_rec(root);
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
    long long ins_val;
    std::cin >> ins_val;

    tree.build(all);

    //задать высоты и баланс
    tree.set_heights();

   // tree.fix();

    tree.add(ins_val);

    tree.set_rec();

    //проверить баланс
    std::cout << n+1 << "\n";
    tree.widthorder();

    return 0;
}
/*
7
-2 7 2
8 4 3
9 0 0
3 5 6
0 0 0
6 0 0
-7 0 0
10

7
-2 7 2
8 4 3
9 0 0
3 5 6
0 0 0
6 0 0
-7 0 0
-9

12
10 2 3
6 4 5
14 6 7
1 0 0
8 0 0
12 8 0
16 0 9
11 0 0
17 0 10
18 0 11
25 12 0
20 0 0
60




*/