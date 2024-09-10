#include "iostream"
#include "string"
#include "vector"


struct Node {
    Node *left;
    Node *right;
    long long data;
    long long size;

    Node() = default;

    explicit Node(long long val) {
        left = nullptr;
        right = nullptr;
        data = val;
        size = 0;
    };
    explicit Node(long long val, long long sub_size) {
        left = nullptr;
        right = nullptr;
        data = val;
        size = sub_size;
    };
};


class BSTree {
private:
    Node *root = nullptr;

    Node *create_rec(std::vector<long long> &a, long long start, long long end) {
        if (start > end) {
            return nullptr;
        }

        long long mid = start + (end - start) / 2;
        Node *cur_node = new Node(a[mid]);

        cur_node->left = create_rec(a, start, mid - 1);

        cur_node->right = create_rec(a, mid + 1, end);


        return cur_node;
    }

    Node *add_rec(Node *cur_node, long long val, long long sub_size) {
        if (cur_node == nullptr) {
            return new Node(val, sub_size);
        } else if (val < cur_node->data) {
            cur_node->size += 1;
            cur_node->left = add_rec(cur_node->left, val, 0);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val, 0);
        }
        return cur_node;
    }

    Node *remove_rec(Node *cur_node, long long val) {
        if (cur_node == nullptr) {
            return cur_node;
        }

        if (val < cur_node->data) {
            --cur_node->size;
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

    Node *find_recursive(Node *cur_node, long long val) {
        if (cur_node == nullptr || val == cur_node->data){
            return cur_node;
        }
        if (val < cur_node->data){
            return find_recursive(cur_node->left, val);
        }
        else if (val > cur_node->data){
            return find_recursive(cur_node->right, val);
        }
    }

    Node *find_kth_L_rec(Node *cur_node, long long val){
        if (cur_node == nullptr){
            return cur_node;
        }

        if (cur_node->size < val){
            return find_kth_L_rec(cur_node->right, val-cur_node->size-1);
        }
        else if (cur_node->size > val){
            return find_kth_L_rec(cur_node->left, val);
        }
        else{
            return cur_node;
        }
    }

public:

    BSTree() = default;

    void add(long long val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        } else {
            add_rec(root, val, 0);
        }
    }

    BSTree(std::vector<long long> &arr, bool sorted) {
        if (!sorted) {
            for (long long i: arr) {
                add(i);
            }
        } else {
            root = create_rec(arr, 0, arr.size() - 1);
        }
    };

    bool find(long long val) {
        return find_recursive(root, val);
    }

    void remove(long long val) {
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

    Node* next(long long val) {
        Node *cur_node = root;
        Node *child = nullptr;
        while (cur_node != nullptr) {
            if (cur_node->data > val) {
                child = cur_node;
                cur_node = cur_node->left;
            } else if (cur_node->data <= val){
                cur_node = cur_node->right;
            }
        }

        return child;
    }

    Node* prev(long long val) {
        Node *cur_node = root;
        Node *child = nullptr;
        while (cur_node != nullptr) {
            if (cur_node->data >= val) {
                cur_node = cur_node->left;
            } else if (cur_node->data < val){
                child = cur_node;
                cur_node = cur_node->right;
            }
        }

        return child;
    }

    long long find_kth_L(long long val){
        Node *tmp = find_kth_L_rec(root, val);
        return tmp ? tmp->data : 0;
    }
};

int main(){
    long long N;
    std::cin >> N;

    std::vector<long long> ans;
    BSTree test;
    long long size = 0;
    long long operation, val;
    for (long long i = 0; i < N; ++i){
        std::cin >> operation >> val;
        if (operation == 1){
            test.add(val);
            ++size;
        }
        else if (operation == 0){
            ans.push_back(test.find_kth_L(size-val));
        }
        else if (operation == -1){
            test.remove(val);
            --size;
        }
    }
    for (long long i = 0; i < ans.size(); ++i){
        std::cout << ans[i] << "\n";
    }

    return 0;
}
/*
11
1 5
1 3
1 7
1 4
1 2
1 1
1 6
1 8
1 10
1 9
0 7

13
1 10
1 3
1 1
1 5
1 8
1 7
1 100
1 15
1 13
1 31
1 -8
1 2
0 2
*/