#ifndef hash_table_h
#define hash_table_h

#include "../header/header.h"

typedef struct hash_table HASH_TABLE;
typedef struct huff_node HUFF_NODE;

struct hash_table {
    unsigned char mapped_bytes[256];
    unsigned char compressed_size[256];
};

/** @return returns a new hash table*/
HASH_TABLE *create_hash_table();

/** @param root: the node of the recursive function*/
/** @param hash_table: where the new mapping will be stored*/
/** @param compressed_file: the file that will have the new mapping wrote*/
/** @param mapping: the current mapping while traversing the tree*/
/** @param compressed_length: the actual length of the new mapping*/
void bytes_mapping(HUFF_NODE *root, HASH_TABLE *hash_table, FILE *compressed_file, unsigned char mapping, int compressed_length);

/** @param root: the root created after dequeueing nodes*/
/** @param compressed_file: the file to be compressed*/
HASH_TABLE *generate_new_mapping(HUFF_NODE *root, FILE *compressed_file);

#endif