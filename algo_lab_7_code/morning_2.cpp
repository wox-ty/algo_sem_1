#include <list>
#include <vector>
#include "iostream"
#include "string"

struct Node {
    Node *left;
    Node *right;
    std::string data;
    long height;
    long balance;
    long prefix;


    Node() = default;

    explicit Node(std::string val) {
        left = nullptr;
        right = nullptr;
        data = val;
        height = 1;
        balance = 0;
        prefix = 0;
    };

};


class BSTree {
public:
    Node *root = nullptr;
private:
    Node *add_rec(Node *cur_node, const std::string& val) {
        if (cur_node == nullptr) {
            ++size;
            return new Node(val);
        } else if (val < cur_node->data) {
            cur_node->left = add_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val);
        }
        return Balance(cur_node);
    }

    long set_height(Node *cur_node) {
        if (cur_node == nullptr) {
            return 0;
        }
        return cur_node->height;
    }

    long set_balance(Node *cur_node) {
        if (cur_node == nullptr) {
            return 0;
        }
        return (set_height(cur_node->right) - set_height(cur_node->left));
    }

    long fix_heights_rec(Node *cur_node) {
        cur_node->height = std::max((cur_node->left ? cur_node->left->height : 0),
                                    (cur_node->right ? cur_node->right->height : 0)) + 1;
        cur_node->balance = ((cur_node->right ? cur_node->right->height : 0) -
                             (cur_node->left ? cur_node->left->height : 0));
        return cur_node->height;
    }

    Node *find_recursive(Node *cur_node, const std::string& val) {
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
    long size = -1;

    BSTree() = default;

    void add(const std::string& val) {
        root = add_rec(root, val);
    }

    Node *find(const std::string& val) {
        Node *tmp = find_recursive(root, val);
        return tmp;
    }
};

struct LZ_Node {
    long pos;
    char next;

    LZ_Node(long p, char n) {
        pos = p;
        next = n;
    }
};

std::list<LZ_Node*> encodeLZ78(std::string s) {
    std::string buffer = "";

    BSTree dict;

    std::list<LZ_Node*> result;

    for (long i = 0; i < s.size(); ++i) {
        if (dict.find(buffer + s[i])) {
            buffer += s[i];
        } else {
            LZ_Node *tmp = new LZ_Node(dict.find(buffer) ? dict.find(buffer)->prefix : 0, s[i]);
            result.push_back(tmp);
            dict.add(buffer + s[i]);
            dict.find(buffer + s[i])->prefix = dict.size + 1;
            buffer = "";
        }
    }
    if (!buffer.empty()) {
        char last = buffer[buffer.size()];
        std::string idx = buffer;
//        std::string sus(1, idx);
        buffer.pop_back();
        LZ_Node *tml = new LZ_Node((dict.find(idx) ? dict.find(idx)->prefix : 0), last);
        result.push_back(tml);
    }

    return result;
}

int main() {
    std::string input;
    std::cin >> input;

    std::list<LZ_Node *> res;

    res = encodeLZ78(input);

    for (auto i: res) {
        std::cout << i->pos << " " << i->next << std::endl;
    }

    return 0;
}
/*
aaaaa

*/