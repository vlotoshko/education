#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>
#include <vector>
#include <fstream>

template< typename Key, typename Value >
class BST {
public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void put(Key k, Value v) { root = put(root, k, v); }
    Value get(Key k) { return get(root, k); }
    void forgetMin() { root = forgetMin(root); }
    void deleteNode(Key k) { root = deleteNode(root, k); }

    int size() { return root ? root->count : 0; }
    bool isEmpty() { return size() != 0; }
    Value valSum() { return valSum(root); }
    Key min() { return min(root)->key; }
    Key max() { return max(root)->key; }
    Key floor(Key k) { Node * n = floor(root, k); return n ? n->key : nullptr; }
    Key ceiling(Key k) { Node * n = ceiling(root, k); return n ? n->key : nullptr; }
    Key select(int r) { Node * n = select(root, r); return n ? n->key : nullptr; }
    int rank(Key k) { return rank(root, k); }
    void print() { print(root); }
    std::vector< Key > keys(Key lo, Key hi);
    std::vector< Key > keys() { return keys(min(), max()); }

    class Node {
    public:
        Node(Key k, Value v) : key(k), val(v), left(nullptr), right(nullptr), count(1) {}
        Key key;
        Value val;
        Node* left;
        Node* right;
        int count;
    };
    Node* root;

private:
    Value get(Node* n, Key k);
    Node* put(Node* n, Key k, Value v);
    Node* forgetMin(Node* n);
    Node* deleteNode(Node* n, Key k);
    void clear(Node* n);
    int size(Node* n);
    Value valSum(Node* n);
    Node* min(Node* n);
    Node* max(Node* n);
    Node* floor(Node* n, Key k);
    Node* ceiling(Node* n, Key k);
    Node* select(Node* n, int k);
    int rank(Node* n, Key k);
    void print(Node* n);
    void keys(Node* n, std::vector< Key >& v, Key lo, Key hi);
};


template< typename Key, typename Value >
Value BST< Key, Value>::get(Node* n,  Key k) {
    if(n == nullptr)
        return nullptr;

    if (k < n->key)
        return get(n->left, k);
    if (k > n->key)
        return get(n->right, k);
    return n->val;
}

template< typename Key, typename Value >
typename BST< Key, Value>::Node* BST< Key, Value>::put(Node* n,  Key k, Value v) {
    if(n == nullptr)
        n = new Node(k, v);

    if (k < n->key)
        n->left = put(n->left, k, v);
    else
        if (k > n->key)
            n->right = put(n->right, k, v);
        else
            if (k == n->key)
                ++n->val; // Value have to do prefix increment
    n->count = (n->left ? n->left->count : 0) + (n->right ? n->right->count : 0) + 1;
    return n;
}

template< typename Key, typename Value >
typename BST< Key, Value>::Node* BST< Key, Value>::forgetMin(Node* n) {
    if(n->left == nullptr)
        return n->right;

    n->left = forgetMin(n->left);
    n->count = size(n->left) + size(n->right) + 1;
    return n;
}

template< typename Key, typename Value >
typename BST< Key, Value>::Node* BST< Key, Value>::deleteNode(Node* n,  Key k) {
    if(n == nullptr)
        return nullptr;

    if (k < n->key)
        n->left = deleteNode(n->left, k);
    else if (k > n->key)
        n->right = deleteNode(n->right, k);
    else {
        if (n->left == nullptr)
            return n->left;
        if (n->right == nullptr)
            return n->right;
        Node* t = n;
        n = min(t->right);
        n->right = forgetMin(t->right);
        n->left = t->left;
    }

    n->count = size(n->left) + size(n->right) + 1;
    return n;
}

template< typename Key, typename Value >
void BST< Key, Value>::clear(Node* n) {
    if(n == nullptr)
        return;

    if (n->left)
        clear(n->left);
    if (n->right)
        clear(n->right);

    delete n;
    n = nullptr;
}

template< typename Key, typename Value >
void BST< Key, Value>::print(Node* n) {
    if(n == nullptr)
        return;

    print(n->left);
    std::cout << n->key << " ";
    print(n->right);
}

template< typename Key, typename Value >
int BST< Key, Value>::size(Node* n) {
    return n ? n->count : 0;
}

template< typename Key, typename Value >
typename BST< Key, Value>::Node* BST< Key, Value>::min(Node* n) {
    if (n->left)
        return min(n->left);
    else
        return n;
}

template< typename Key, typename Value >
typename BST< Key, Value>::Node* BST< Key, Value>::max(Node* n) {
    if (n->right)
        return max(n->right);
    else
        return n;
}

template< typename Key, typename Value >
typename BST< Key, Value>::Node* BST< Key, Value>::floor(Node* n, Key k) {
    if (n == nullptr)
        return nullptr;

    if (n->key == k)
        return n;

    if (n->key > k)
        return floor(n->left, k);

    Node* t = floor(n->right, k);
    return t ? t : n;
}

template< typename Key, typename Value >
typename BST< Key, Value>::Node* BST< Key, Value>::ceiling(Node* n, Key k) {
    if (n == nullptr)
        return nullptr;

    if (n->key == k)
        return n;

    if (n->key < k)
        return ceiling(n->right, k);

    Node* t = ceiling(n->left, k);
    return t ? t : n;
}

template< typename Key, typename Value >
typename BST< Key, Value>::Node* BST< Key, Value>::select(Node* n, int k) {
    if (n == nullptr)
        return nullptr;

    int t = size(n->left);

    if (t > k)
        return select(n->left, k);
    else
        if (t < k)
            return select(n->right, k - t - 1);
        else
            return n;
}

template< typename Key, typename Value >
int BST< Key, Value>::rank(Node* n,  Key k) {
    if(n == nullptr)
        return 0;

    if (k < n->key)
        return rank(n->left, k);
    else
        if (k > n->key)
            return 1 + size(n->left) + rank(n->right, k);
        else
            return size(n->left);
}

template< typename Key, typename Value >
void BST< Key, Value >::keys(Node* n, std::vector< Key >& v, Key lo, Key hi) {
    if (n == nullptr)
        return;

    if (n->key >= lo)
        keys(n->left, v, lo, hi);

    if (n->key >= lo && n->key <= hi)
        v.push_back(n->key);

    if (n->key <= hi)
        keys(n->right, v, lo, hi);
}

template< typename Key, typename Value >
std::vector< Key > BST< Key, Value >::keys(Key lo, Key hi) {
    std::vector< Key > vec;
    keys(root, vec, lo, hi);
    return vec;
}

template< typename Key, typename Value >
Value BST< Key, Value>::valSum(Node* n) {
    if(n == nullptr)
        return 0;

    Value i = 0;
    if (n->left)
        i += valSum(n->left);
    if (n->right)
        i += valSum(n->right);

    i += n->val;

    return i;
}

int testBst(int argc, char *argv[]);

#endif // SEARCH_H
