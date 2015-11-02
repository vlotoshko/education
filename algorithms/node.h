#ifndef NODE
#define NODE

template< typename Value >
class Node {
public:
    Node(Value v = 0) : val(v), next(nullptr), marked_(false) {}
    ~Node();
    Value val;
    Node* next;
    Node* last();
    Node* add(Node* n);
    void clear();
private:
     bool marked_;
};

template< typename Value >
Node< Value >* Node< Value >::last() {
    marked_ = true;

    Node* n;
    if (next != nullptr && !next->marked_) {
        n = next->last();
    }
    else
        n = this;

    marked_ = false;
    return n;
}

template< typename Value >
void Node< Value >::clear() {
    marked_ = true;
    if (next != nullptr) {
        if (!next->marked_)
            delete next;
    }
    marked_ = false;
}

template< typename Value >
Node< Value >::~Node< Value >() {
    clear();
}

template< typename Value >
Node< Value >* Node<Value>::add(Node *n) {
//    n->last()->next = next;
//    next = n;
    last()->next = n;
    return this;
}

#endif // NODE

