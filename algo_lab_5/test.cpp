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
    std::vector<long> fake;
    std::vector<long> vect;

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

    void vectorder_rec(Node *cur_node) {
        if (cur_node != nullptr) {
            vectorder_rec(cur_node->left);
            vect.push_back(cur_node->data);
            vectorder_rec(cur_node->right);
        }
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

    void vectorder() {
        vectorder_rec(root);
    }

    void destruct() {
        while (root != nullptr) {
            remove(findMin(root)->data);
        }
        fake.clear();
    }

    std::vector<long> Get_fake() {
        return fake;
    }

    std::vector<long> Get_vect() {
        return vect;
    }

    void del_vec() {
        vect.clear();
    }
};

void merge(BSTree &uno, BSTree &dos) {
    dos.vectorder();
    std::vector<long> cur = dos.Get_vect();
    for (int i = 0; i < cur.size(); ++i) {
        uno.add(cur[i]);
    }
}

int main() {
    long n;
    std::cin >> n;

    std::string operation;
    int account;
    long id;

    BSTree first;
    BSTree second;

    long merge_count = 0;

    std::vector<std::vector<long>> ans;

    for (long i = 0; i < n; ++i) {
        std::cin >> operation;

        if (operation == "buy") {
            std::cin >> account >> id;
            if (account == 1) {
                first.add(id);
            } else if (account == 2) {
                second.add(id);
            }
        } else if (operation == "sell") {
            std::cin >> account >> id;
            if (account == 1) {
                first.remove(id);
            } else if (account == 2) {
                second.remove(id);
            }
        } else if (operation == "merge") {
            merge(first, second);
            second.destruct();
            second.del_vec();

            first.vectorder();
            ans.push_back(first.Get_vect());
            first.del_vec();

            ++merge_count;
        }
    }

    for (int i = 0; i < merge_count; ++i) {
        for (int j = 0; j < ans[i].size(); ++j) {
            std::cout << ans[i][j];
            if (j != ans[i].size() - 1) {
                std::cout << " ";
            }
        }

        if (i != merge_count - 1 && !ans[i].empty()) {
            std::cout << "\n";
        }
    }

    return 0;
}
/*
3
buy 1 2
buy 2 3
merge

5
buy 1 2
buy 2 3
merge
buy 2 4
merge

8
buy 1 2
buy 2 3
merge
buy 2 4
merge
buy 2 7
sell 2 7
merge

4
buy 2 1
buy 2 3
buy 2 5
merge


5
buy 2 1
buy 2 3
buy 2 5
merge
buy 1 2

7
buy 2 1
buy 2 3
buy 2 5
merge
sell 1 3
buy 1 2
merge
*/