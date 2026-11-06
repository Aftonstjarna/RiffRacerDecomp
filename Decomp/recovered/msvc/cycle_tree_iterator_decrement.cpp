struct Node {
    Node *left;
    Node *parent;
    Node *right;
    unsigned char color;
    unsigned char sentinel;
};
struct TreeIterator {
    Node *node;
    TreeIterator *decrement();
};
TreeIterator *TreeIterator::decrement() {
    if (node->sentinel) {
        node = node->right;
    } else if (!node->left->sentinel) {
        Node *next = node->left;
        while (!next->right->sentinel)
            next = next->right;
        node = next;
    } else {
        Node *next = node->parent;
        while (!next->sentinel && node == next->left) {
            node = next;
            next = next->parent;
        }
        if (!node->sentinel)
            node = next;
    }
    return this;
}
