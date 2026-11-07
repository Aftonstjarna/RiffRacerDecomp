struct Node {
    Node* left;
    Node* parent;
    Node* right;
    unsigned char color;
    unsigned char sentinel;
};
struct Tree {
    Node* head;
    void rotate_right(Node* node);
};
void Tree::rotate_right(Node* node) {
    Node* pivot = node->left;
    node->left = pivot->right;
    if (!pivot->right->sentinel)
        pivot->right->parent = node;
    pivot->parent = node->parent;
    if (node == head->parent)
        head->parent = pivot;
    else if (node == node->parent->right)
        node->parent->right = pivot;
    else
        node->parent->left = pivot;
    pivot->right = node;
    node->parent = pivot;
}
