#ifndef decompressor_h
#define decompressor_h

#include "../header/header.h"
#include "../huff_tree/huff_tree.h"
#include "../hash/hash.h"
#include "../heap/heap.h"

 /** @param compressed_file: the file that holds the compressed bytes*/
 /** @param decompressed_file: the file that will hold the decompressed bytes*/
 /** @param root: the root of the huffman tree, previously taken from the compressed file*/
 /** @param trash_size: the trash size previousle taken from the compressed_file*/
void print_decompressed_file(FILE *compressed_file, FILE *decompressed_file, HUFF_NODE *root, int trash_size);

/** @param compressed_file: the file that holds the preorder tree*/
/** @param tree: the root of the tree*/
/** @return returns the root of the tree */
HUFF_NODE *tree_from_header(FILE *compressed_file, HUFF_NODE *tree);

/** @param compressed_file: the file that was previously compressed*/
/** @param compressed_path: the path to the compressed file*/
/** @return returns the decompressed file*/
FILE* decompress(FILE *compressed_file, char *compressed_path);

#endif