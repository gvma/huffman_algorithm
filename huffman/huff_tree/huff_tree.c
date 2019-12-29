#include "huff_tree.h"

void print_huff_tree(HUFF_NODE *root) {
    if (root) {
        printf("%c", root->key);
        print_huff_tree(root->left);
        print_huff_tree(root->right);
    }
}

bool is_leaf(HUFF_NODE *root) {
    return root->left == NULL && root->right == NULL;
}

HUFF_NODE *create_huff_node(long long int frequency, unsigned char key, HUFF_NODE *left, HUFF_NODE *right) {
    HUFF_NODE *new_huff_node = (HUFF_NODE *)malloc(sizeof(HUFF_NODE));
    new_huff_node->frequency = frequency;
    new_huff_node->key = key;
    new_huff_node->left = left;
    new_huff_node->right = right;
    return new_huff_node;
}