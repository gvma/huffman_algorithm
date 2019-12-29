#ifndef huff_tree_h
#define huff_tree_h

#include "../header/header.h"
#include "../hash/hash.h"

struct huff_node {
    long long int frequency;
    unsigned char key;
    HUFF_NODE *right, *left;
};

typedef struct huff_node HUFF_NODE;

/** @param root: the huffman tree root*/
void print_huff_tree(HUFF_NODE *root);

/** @param root: the node that will be compared if it is a leaf*/
bool is_leaf(HUFF_NODE *root);

// void bytes_mapping(HUFF_NODE *root, HASH_TABLE *hash_table, FILE *compressed_file, unsigned char mapping, int compressed_length) {
    
// }

/** @param frequency: a number that represents the frequency of a byte in the file*/
/** @param key: the byte that appeared in the file*/
/** @param left: the left child of the huffman node*/
/** @param right: the right child of the huffman node*/
/** @return returns a huffman node with the parameters above*/
HUFF_NODE *create_huff_node(long long int frequency, unsigned char key, HUFF_NODE *left, HUFF_NODE *right);

#endif