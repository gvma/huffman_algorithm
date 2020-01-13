#include "decompressor.h"

void print_decompressed_file(FILE *compressed_file, FILE *decompressed_file, HUFF_NODE *root, int trash_size) {
    HUFF_NODE *tree = root;
    unsigned char byte, i, aux;
    fscanf(compressed_file, "%c", &byte);
    while(true) {
        if(fscanf(compressed_file, "%c", &aux) == EOF) {
            for(int i = 7; i >= trash_size; --i) {
                if(is_leaf(tree)) {
                    fprintf(decompressed_file, "%c", tree->key);
                    tree = root;
                }
                if(byte >> i & 1) {
                    tree = tree->right;
                } 
                else {
                    tree = tree->left;
                }
            }
            break;
        } else {
            for(int i = 7; i >= 0; --i) {
                if(is_leaf(tree)) {
                    fprintf(decompressed_file, "%c", tree->key);
                    tree = root;
                }
                if(byte >> i & 1) {
                    tree = tree->right;
                }
                else {
                    tree = tree->left;
                }
            }
        }
        byte = aux;
    }
    fprintf(decompressed_file, "%c", tree->key);
}

HUFF_NODE *tree_from_header(FILE *compressed_file, HUFF_NODE *tree) {
    unsigned char byte;
    fscanf(compressed_file, "%c", &byte);
    if (byte != '*')  {
        if (byte == '\\') {
            fscanf(compressed_file, "%c", &byte);
        }
        tree = create_huff_node(0, byte, NULL, NULL);
    } else {
        tree = create_huff_node(0, '*', NULL, NULL);
        tree->left = tree_from_header(compressed_file, tree->left);
        tree->right = tree_from_header(compressed_file, tree->right);
    }
    return tree;
}

FILE* decompress(FILE *compressed_file, char *compressed_path) {
    unsigned char byte, first_byte, second_byte;
    fscanf(compressed_file, "%c%c", &first_byte, &second_byte);

    int trash_size = (first_byte >> 5);
    first_byte <<= 3, first_byte >>= 3;
    short int huffman_tree_size = first_byte;
    huffman_tree_size <<= 8;
    huffman_tree_size |= second_byte;

    printf("Trash Size: %d and Tree Size: %d\n", trash_size, huffman_tree_size);
    char decompressed_path[100], i;
    for (i = 0; i < strlen(compressed_path) - 5; ++i) {
        decompressed_path[i] = compressed_path[i];
    }
    decompressed_path[i] = '\0';

    FILE *decompressed_file = fopen(decompressed_path, "wb");
    HUFF_NODE *root;
    print_decompressed_file(compressed_file, decompressed_file, tree_from_header(compressed_file, root), trash_size);
    return decompressed_file;
}