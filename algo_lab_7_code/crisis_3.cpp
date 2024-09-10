#include <iostream>
#include <queue>
#include <utility>

struct Node {
    Node *left;
    Node *right;
    char data;
    long height;
    long balance;
    long freq;
    std::string code;


    Node() = default;

    explicit Node(char val) {
        left = nullptr;
        right = nullptr;
        data = val;
        height = 1;
        balance = 0;
        freq = 1;
        code = "";
    };


    explicit Node(char val, std::string tx) {
        left = nullptr;
        right = nullptr;
        data = val;
        height = 1;
        balance = 0;
        freq = 1;
        code = tx;
    };
};


class BSTree {
public:
    Node *root = nullptr;
private:
    std::vector<Node*> vecty;

    Node *add_rec(Node *cur_node, char val) {
        if (cur_node == nullptr) {
            return new Node(val);
        } else if (val < cur_node->data) {
            cur_node->left = add_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val);
        } else if (val == cur_node->data){
            ++cur_node->freq;
        }
        return Balance(cur_node);
    }

    Node *add_rec(Node *cur_node, char val, std::string code) {
        if (cur_node == nullptr) {
            return new Node(val, code);
        } else if (val < cur_node->data) {
            cur_node->left = add_rec(cur_node->left, val, code);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val, code);
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

    Node *remove_rec(Node *cur_node, char val) {
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

    Node *find_recursive(Node *cur_node, char val) {
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

    void vec_rec(Node *node) {
        if (node != nullptr) {
            vec_rec(node->left);
            vecty.push_back(node);
            vec_rec(node->right);
        }
    }

public:

    BSTree() = default;

    void add(char val) {
        root = add_rec(root, val);
    }

    void add(char val, std::string code) {
        root = add_rec(root, val, code);
    }

    Node* find(char val) {
        Node *tmp = find_recursive(root, val);
        return tmp;
    }

    void remove(char val) {
        root = remove_rec(root, val);
    }

    Node *prev(char val) {
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

    std::vector<Node*> vec(){
        vec_rec(root);
        return vecty;
    }
};


struct HAF_NODE {
    char data;
    int frequency;
    HAF_NODE* left;
    HAF_NODE* right;
};

HAF_NODE* create_Haf_Node(char data, int frequency, HAF_NODE* left, HAF_NODE* right) {
    HAF_NODE* newHAF_NODE = new HAF_NODE();
    newHAF_NODE->data = data;
    newHAF_NODE->frequency = frequency;
    newHAF_NODE->left = left;
    newHAF_NODE->right = right;
    return newHAF_NODE;
}

struct freq_comp {
    bool operator()(HAF_NODE* left, HAF_NODE* right) {
        return left->frequency > right->frequency;
    }
};

HAF_NODE* Haff_build(const std::string& input) {
    std::priority_queue<HAF_NODE*, std::vector<HAF_NODE*>, freq_comp> pq;

    BSTree frequencyMap;
    for (char c : input) {
        frequencyMap.add(c);
    }

    std::vector<Node*> tmp = frequencyMap.vec();

    for (auto i : tmp){
        pq.push(create_Haf_Node(i->data, i->freq, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        HAF_NODE* left = pq.top();
        pq.pop();
        HAF_NODE* right = pq.top();
        pq.pop();

        int sumFrequency = left->frequency + right->frequency;
        pq.push(create_Haf_Node('\0', sumFrequency, left, right));
    }

    return pq.top();
}

void Table_build(HAF_NODE* root, std::string code, BSTree& encodingTable) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '\0') {
        encodingTable.add(root->data, code);
    }

    Table_build(root->left, code + "0", encodingTable);
    Table_build(root->right, code + "1", encodingTable);
}

std::string encode(const std::string& input, BSTree& encodingTable) {
    std::string encode;
    for (char c : input) {
        encode += encodingTable.find(c)->code;
    }
    return encode;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string input;
    std::cin >> input;
    HAF_NODE* root = Haff_build(input);
    BSTree Table;
    Table_build(root, "", Table);
    std::string output;
    output = encode(input, Table);

    std::cout << output.size() << "\n";

    return 0;
}
