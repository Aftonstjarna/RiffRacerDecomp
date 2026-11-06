struct Node {
    Node* left;
    Node* parent;
    Node* right;
    unsigned char color;
    unsigned char is_nil;
};
struct TreeIterator {
    Node* node;
    TreeIterator& increment();
};
TreeIterator& TreeIterator::increment() {
    if (!node->is_nil) {
        if (!node->right->is_nil) {
            Node* next = node->right;
            while (!next->left->is_nil)
                next = next->left;
            node = next;
        } else {
            Node* next = node->parent;
            while (!next->is_nil && node == next->right) {
                node = next;
                next = next->parent;
            }
            node = next;
        }
    }
    return *this;
}
