#include "iostream"
#include "string"
#include "vector"


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

    Node* next(long val) {
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

//        if (child != NULL) {
//            return std::to_string(child->data);
//        } else {
//            return "none";
//        }
        return child;
    }

    Node* prev(long val) {
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

//        if (child != NULL) {
//            return std::to_string(child->data);
//        } else {
//            return "none";
//        }
        return child;
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    BSTree test;
    std::string operation;
    long val;
    while (std::cin >> operation) {
        if (operation == "insert") {
            std::cin >> val;
            test.add(val);
        } else if (operation == "exists") {
            std::cin >> val;
            if (test.find(val)) {
                std::cout << "true" << "\n";
            } else {
                std::cout << "false" << "\n";
            }
        } else if (operation == "next") {
            std::cin >> val;
            if (test.next(val) != nullptr){
                std::cout << test.next(val)->data << "\n";
            }
            else{
                std::cout << "none" << "\n";
            }
//            std::cout << test.next(val)->data << "\n";
        } else if (operation == "prev") {
            std::cin >> val;
            if (test.prev(val) != nullptr){
                std::cout << test.prev(val)->data << "\n";
            }
            else{
                std::cout << "none" << "\n";
            }
//            std::cout << test.prev(val)->data << "\n";
        } else if (operation == "delete") {
            std::cin >> val;
            test.remove(val);
        }
        if (operation == "break") {
            break;
        }
    }

    return 0;
}