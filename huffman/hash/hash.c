#include "hash.h"

HASH_TABLE *create_hash_table() {
    HASH_TABLE *hash_table = (HASH_TABLE *)malloc(sizeof(HASH_TABLE));
    int i;
    for (i = 0; i < 256; ++i) {
        hash_table->mapped_bytes[i] = 0;
        hash_table->compressed_size[i] = 0;
    }
    return hash_table;
}

extern void bytes_mapping(HUFF_NODE *root, HASH_TABLE *hash_table, FILE *compressed_file, unsigned char mapping, int compressed_length) {
    
}

extern HASH_TABLE *generate_new_mapping(HUFF_NODE *root, FILE *compressed_file) {
    HASH_TABLE *hash_table = create_hash_table();
    unsigned char mapping = 0;
    int compressed_length = 0;
    bytes_mapping(root, hash_table, compressed_file, mapping, compressed_length);
}