#include "iostream"
#include "string"
#include "vector"


struct Node {
    Node *left;
    Node *right;
    long long data;

    Node() = default;

    explicit Node(long long val) {
        left = nullptr;
        right = nullptr;
        data = val;
    };
};


class BSTree {
private:
    std::vector<long long> inord;
    std::vector<long long> postord;

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

    Node *add_rec(Node *cur_node, long long val) {
        if (cur_node == nullptr) {
            return new Node(val);
        } else if (val < cur_node->data) {
            cur_node->left = add_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val);
        }
        return cur_node;
    }

    Node *remove_rec(Node *cur_node, long long val) {
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
            postord.push_back(node->data);
//            std::cout << node->data << " ";
        }
    }

    void inorder_rec(Node *node) {
        if (node != nullptr) {
            inorder_rec(node->left);
            inord.push_back(node->data);
//            std::cout << node->data << " ";
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

    Node* create_tree_rec(std::vector<long long>& arr, long long& i, long long min, long long max) {
        if (i >= arr.size()) {
            return nullptr;
        }

        if (arr[i] < min || arr[i] > max) {
            return nullptr;
        }

        Node* cur_node = new Node(arr[i]);
        ++i;

        if (i < arr.size() && arr[i] < cur_node->data && arr[i] >= min) {
            cur_node->left = create_tree_rec(arr, i, min, cur_node->data);
        }
        if (i < arr.size() && arr[i] >= cur_node->data && arr[i] < max) {
            cur_node->right = create_tree_rec(arr, i, cur_node->data, max);
        }


        return cur_node;
    }

public:

    BSTree() = default;

    void add(long long val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        } else {
            add_rec(root, val);
        }
    }
    void add(Node* address, long long val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        } else {
            add_rec(address, val);
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

    std::string next(long long val) {
        Node *cur_node = root;
        Node *child = nullptr;
        while (cur_node != nullptr) {
            if (cur_node->data > val) {
                child = cur_node;
                cur_node = cur_node->left;
            } else if (cur_node->data < val){
                cur_node = cur_node->right;
            }
        }

        if (child != NULL) {
            return std::to_string(child->data);
        } else {
            return "none";
        }
    }

    Node* prev(long long val) {
        Node *cur_node = root;
        Node *child = nullptr;
        while (cur_node != nullptr) {
            if (cur_node->data > val) {
                cur_node = cur_node->left;
            } else if (cur_node->data < val){
                child = cur_node;
                cur_node = cur_node->right;
            }
        }

        return child;
    }

    std::vector<long long> GetINORD(){
        return inord;
    }

    std::vector<long long> GetPOSTORD(){
        return postord;
    }

    void create_tree_from_pre(std::vector<long long> &arr) {
        long long IDX = 0;
        root = create_tree_rec(arr, IDX,LONG_LONG_MIN, LONG_LONG_MAX);
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n;
    std::cin >> n;
    std::vector<long long> pre;
    std::vector<long long> in;
    std::vector<long long> post;
    pre.resize(n);
    in.resize(n);
    post.resize(n);

    for (long long i = 0; i < n; ++i){
        std::cin >> pre[i];
    }
    for (long long j = 0; j < n; ++j){
        std::cin >> in[j];
    }
    for (long long k = 0; k < n; ++k){
        std::cin >> post[k];
    }


    BSTree tree;

    tree.create_tree_from_pre(pre);

    tree.inorder();
    tree.postorder();

    if (in == tree.GetINORD() && post == tree.GetPOSTORD()){
        std::cout << "YES";
    } else{
        std::cout << "NO";
    }

    return 0;
}