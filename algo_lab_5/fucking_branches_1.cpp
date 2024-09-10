#include "iostream"
#include "vector"


struct Node {
    Node *left;
    Node *right;
    long data;

    Node() = default;

    Node(long val) {
        left = nullptr;
        right = nullptr;
        data = val;
    };
};


class BSTree {
private:
    Node *root = nullptr;

    Node *create_rec(std::vector<long> &a, long start, long end){
        if (start > end){
            return nullptr;
        }

        long mid = start + (end - start) / 2;
        Node *cur_node = new Node(a[mid]);

        cur_node->left = create_rec(a, start, mid - 1);

        cur_node->right = create_rec(a, mid + 1, end);


        return cur_node;
    }

    void add_rec(Node *cur_node, long val) {
        if (val == cur_node->data){
            if (cur_node->right == nullptr){
                cur_node->right = new Node(val);
            }
            else if (cur_node->right == nullptr){
                cur_node->left = new Node(val);
            }
        }
        else if (val < cur_node->data) {
            if (cur_node->left == nullptr) {
                cur_node->left = new Node(val);
            } else {
                add_rec(cur_node->left, val);
            }
        }
        else if (cur_node->data < val){
            if (cur_node->right == nullptr) {
                cur_node->right = new Node(val);
            } else {
                add_rec(cur_node->right, val);
            }
        }
    }

    Node *remove_rec(Node *cur_node, long val) {
        if (cur_node == nullptr) {
            return cur_node;
        }
        if (cur_node->data > val) {
            cur_node->left = remove_rec(cur_node->left, val);
        } else if (cur_node->data < val) {
            cur_node->right = remove_rec(cur_node->right, val);
        } else {
            if (cur_node->left == nullptr) {
                Node *temp = cur_node->right;
                delete cur_node;
                return temp;
            } else if (cur_node->right == nullptr) {
                Node *temp = cur_node->left;
                delete cur_node;
                return temp;
            }
            Node *temp = findMin(cur_node->right);
            cur_node->data = temp->data;
            cur_node->right = remove_rec(cur_node->right, temp->data);
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

    Node *findMin(Node *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    bool find_recursive(Node *node, long val) {
        if (node == nullptr) {
            return false;
        }
        if (node->data == val) {
            return true;
        }
        if (node->data > val) {
            return find_recursive(node->left, val);
        }
        if (node->data < val) {
            return find_recursive(node->right, val);
        }
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

    BSTree(std::vector<long> &arr, bool sorted) {
        if (!sorted) {
            for (long i: arr) {
                add(i);
            }
        } else {
            root = create_rec(arr, 0, arr.size()-1);
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
};


int main() {
    long N;
    std::cin >> N;
    std::vector<long> test;
    test.resize(N);

    for (long i = 0; i < N; ++i) {
        std::cin >> test[i];
    }

    BSTree base(test, true);

    base.preorder();

    return 0;
}