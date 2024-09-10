#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, int freq) : data(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(HuffmanNode* lhs, HuffmanNode* rhs) {
        return lhs->frequency > rhs->frequency;
    }
};

void generateCodes(HuffmanNode* root, const string& code, vector<string>& codes) {
    if (root!= nullptr) {
        if (!root->left && !root->right) {
            codes[root->data] = code;
        }
        generateCodes(root->left, code + "0", codes);
        generateCodes(root->right, code + "1", codes);
    }
}

vector<string> buildHuffmanTree(const string& input) {
    vector<int> frequencies(256, 0);

    for (char c : input) {
        frequencies[static_cast<unsigned char>(c)]++;
    }
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
    for (int i = 0; i < 256; ++i) {
        if (frequencies[i] > 0) {
            pq.push(new HuffmanNode(static_cast<char>(i), frequencies[i]));
        }
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    vector<string> codes(256, "");
    generateCodes(pq.top(), "", codes);

    while (!pq.empty()) {
        HuffmanNode* node = pq.top();
        pq.pop();
        delete node;
    }

    return codes;
}

string encodeHuffman( string& input, vector<string>& codes) {
    string encoded;
    for (char c : input) {
        encoded += codes[c];
    }
    return encoded;
}

int main() {
    string input;
    cin>>input;

    vector<string> codes = buildHuffmanTree(input);
    string encoded = encodeHuffman(input, codes);


    cout<< encoded.length() << '\n';
}