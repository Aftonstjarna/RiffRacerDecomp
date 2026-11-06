struct TreeNode {
    TreeNode* left;
    TreeNode* parent;
    TreeNode* right;
    unsigned char color;
    unsigned char is_nil;
    TreeNode* rightmost();
};

TreeNode* TreeNode::rightmost()
{
    TreeNode* node = this;
    while (!node->right->is_nil)
        node = node->right;
    return node;
}
