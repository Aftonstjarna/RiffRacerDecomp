struct Node {
    Node* left;
    Node* parent;
    Node* right;
    unsigned char color;
    unsigned char nil;
};
struct Tree {
    Node* head;
    void rotate_left(Node* node);
};
void Tree::rotate_left(Node* node) {
    Node* pivot = node->right;
    node->right = pivot->left;
    if (!pivot->left->nil)
        pivot->left->parent = node;
    pivot->parent = node->parent;
    if (node == head->parent)
        head->parent = pivot;
    else if (node == node->parent->left)
        node->parent->left = pivot;
    else
        node->parent->right = pivot;
    pivot->left = node;
    node->parent = pivot;
}
