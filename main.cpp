#include <bits/stdc++.h>
using namespace std;

// Build tree from extended preorder until encountering -2 terminator in input stream
// Values: -1 => null, 0/1 => node
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v): val(v), left(nullptr), right(nullptr) {}
};

// Read tokens into a vector first to easily manage -2 termination
static bool read_tokens(vector<int>& a){
    a.clear();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x;
    bool has=false;
    while (cin >> x){
        if (x == -2) break;
        a.push_back(x);
        has=true;
    }
    return has;
}

// Build tree from extended preorder sequence with index
Node* build(const vector<int>& a, int& i){
    if (i >= (int)a.size()) return nullptr; // safety
    int v = a[i++];
    if (v == -1) return nullptr;
    Node* root = new Node(v);
    root->left = build(a, i);
    root->right = build(a, i);
    return root;
}

// Prune zero-only subtrees; return pruned subtree pointer, also delete removed nodes to avoid leaks
Node* prune(Node* root){
    if (!root) return nullptr;
    root->left = prune(root->left);
    root->right = prune(root->right);
    if (root->val == 0 && root->left == nullptr && root->right == nullptr){
        delete root;
        return nullptr;
    }
    return root;
}

// Output preorder with -1 for nulls
void print_pre(const Node* root, vector<int>& out){
    if (!root){
        out.push_back(-1);
        return;
    }
    out.push_back(root->val);
    print_pre(root->left, out);
    print_pre(root->right, out);
}

// Delete entire tree to avoid leaks (postorder)
void destroy(Node* root){
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

int main(){
    vector<int> tokens;
    if (!read_tokens(tokens)) return 0;
    int idx = 0;
    Node* root = build(tokens, idx);
    root = prune(root);
    vector<int> out;
    print_pre(root, out);
    // If entire tree pruned to null, print single -1 as per extended preorder of empty tree
    // Our print_pre already prints -1 for nullptr root
    for (size_t i = 0; i < out.size(); ++i){
        if (i) cout << ' ';
        cout << out[i];
    }
    cout << '\n';
    destroy(root);
    return 0;
}

