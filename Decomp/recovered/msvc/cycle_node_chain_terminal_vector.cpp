struct Node {
    unsigned char prefix[432];
    float vector[4];
    Node* next;
    float* terminal_vector();
};
float* Node::terminal_vector() {
    Node* node = this;
    while (node->next)
        node = node->next;
    return node->vector;
}
