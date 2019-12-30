#ifndef compressor_h
#define compressor_h

#include "../header/header.h"
#include "../huff_tree/huff_tree.h"
#include "../hash/hash.h"
#include "../heap/heap.h"

/** @param frequency: an array that will hold the frequency of each character in the file*/
/** @param file: the file that will be read*/
void compose_frequency_array(long long int *frequency, FILE *file);

/** @param file: the file that will be read*/
int compress(FILE *file);

/** @param first_header_bytes: the first two bytes that will compose the header */
/** @param huffman_tree_size: the size of huffman tree*/
/** @param trash_size: the amount of trash from the compressed bytes*/
/** @param compressed_file: the file that will hold the compressed bytes*/
void print_first_header_bytes(unsigned char *first_header_bytes, long long int huffman_tree_size, int trash_size, FILE *compressed_file);

#endif