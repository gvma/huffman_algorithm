#include "huff_tree.h"

void print_huff_tree(HUFF_NODE *root, FILE *compressed_file) {
    if (root) {
        if (is_leaf(root)) {
            if (root->key == '*' || root->key == '\\') {
                fprintf(compressed_file, "\\%c", root->key);
            } else {
                fprintf(compressed_file, "%c", root->key);
            }
        } else {
            fprintf(compressed_file, "%c", root->key);
            print_huff_tree(root->left, compressed_file);
            print_huff_tree(root->right, compressed_file);
        }
    }
}

bool is_leaf(HUFF_NODE *root) {
    return root->left == NULL && root->right == NULL;
}

void bytes_mapping(HUFF_NODE *root, HASH_TABLE *hash_table, unsigned short mapping, int depth, int *trash_size) {
    if (root) {
        if (is_leaf(root)) {
            hash_table->new_mapping[root->key][0] = depth;
            hash_table->new_mapping[root->key][1] = mapping >> 8;
            hash_table->new_mapping[root->key][2] = mapping;
            *trash_size += (root->frequency * depth);
        } else {
            mapping <<= 1;
            bytes_mapping(root->left, hash_table, mapping, depth + 1, trash_size);
            mapping++;
            bytes_mapping(root->right, hash_table, mapping, depth + 1, trash_size);
        }
    }
}

HUFF_NODE *create_huff_node(long long int frequency, unsigned char key, HUFF_NODE *left, HUFF_NODE *right) {
    HUFF_NODE *new_huff_node = (HUFF_NODE *)malloc(sizeof(HUFF_NODE));
    new_huff_node->frequency = frequency;
    new_huff_node->key = key;
    new_huff_node->left = left;
    new_huff_node->right = right;
    return new_huff_node;
}

void get_huff_tree_size(HUFF_NODE *root, long long int *huff_tree_size) {
    if (root) {
        if (is_leaf(root)) {
            if (root->key == '*' || root->key == '\\') {
                *huff_tree_size += 1;
            }
        }
        *huff_tree_size += 1;
        get_huff_tree_size(root->left, huff_tree_size);
        get_huff_tree_size(root->right, huff_tree_size);
    }
}

HUFF_NODE *build_tree(HEAP *queue) {
    unsigned char root_char = '*';
    HUFF_NODE *root_node;
    while (queue->size != 1) {
        HUFF_NODE *left_child = dequeue(queue);
        HUFF_NODE *right_child = dequeue(queue);
        root_node = create_huff_node(left_child->frequency + right_child->frequency, root_char, left_child, right_child);
        enqueue(queue, root_node);
    }
    return root_node;
}

HUFF_NODE *generate_tree(char *pre_order_tree, int *position) {
    HUFF_NODE *root = NULL;
    if (pre_order_tree[*position] == '*') {
        
    }
}