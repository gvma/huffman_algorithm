#ifndef hash_table_h
#define hash_table_h

#include "../header/header.h"
#include "../huff_tree/huff_tree.h"

typedef struct hash_table HASH_TABLE;
typedef struct huff_node HUFF_NODE;

struct hash_table {
    unsigned char new_mapping[256][3];
};

/** @return returns a new hash table*/
HASH_TABLE *create_hash_table();

/** @param root: the root created after dequeueing nodes*/
/** @param compressed_file: the file to be compressed*/
/** @param trash_size: the reference to a variable that holds the trash size*/
/** @return returns the new mapping in a hash table*/
HASH_TABLE *generate_new_mapping(HUFF_NODE *root, FILE *compressed_file, int *trash_size);

/** @param hash_table: the hash table to be printed*/
void print_hash_table(HASH_TABLE *hash_table);

#endif