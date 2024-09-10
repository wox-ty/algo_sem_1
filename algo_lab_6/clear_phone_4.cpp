#include <set>
#include "iostream"
#include "string"


struct Node {
    Node *left;
    Node *right;
    std::string data;
    int height;
    int balance;


    Node() = default;

    explicit Node(std::string val) {
        left = nullptr;
        right = nullptr;
        data = val;
        height = 1;
        balance = 0;
    };
};

int get_unique(const std::string& s){
    int symbols[256];

    for (int i = 0; i < 256; i++) {
        symbols[i] = 0;
    }

    for (int i = 0; i < s.size(); ++i) {
        symbols[s[i]] = 1;
    }

    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (symbols[i] == 1) {
            count++;
        }
    }

    return count;
}

class BSTree {
public:
    Node *root = nullptr;
    int deleted_el = 0;
private:
    Node *add_rec(Node *cur_node, const std::string& val) {
        if (cur_node == nullptr) {
            return new Node(val);
        } else if (val < cur_node->data) {
            cur_node->left = add_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val);
        } else if (val == cur_node->data){
            deleted_el += get_unique(val);
        }
        return Balance(cur_node);
    }

    int set_height(Node* cur_node){
        if (cur_node == nullptr){
            return 0;
        }
        return cur_node->height;
    }

    int set_balance(Node* cur_node){
        if (cur_node == nullptr){
            return 0;
        }
        return (set_height(cur_node->right) - set_height(cur_node->left));
    }
    
    int fix_heights_rec(Node *cur_node){
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

public:

    BSTree() = default;

    void add(const std::string& val) {
        root = add_rec(root, val);
    }

    int GetDeleted(){
        return deleted_el;
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    BSTree tree;
    std::string contact;
    int a = 1;
    for (int i = 0; i < n; ++i){
        std::cin >> contact;
        tree.add(contact);
    }

    std::cout << tree.GetDeleted();

    return 0;
}