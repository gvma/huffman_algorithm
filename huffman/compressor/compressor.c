#include "compressor.h"

void compose_frequency_array(long long int *frequency, FILE *file) {
    unsigned char byte;
    while (fscanf(file, "%c", &byte) != EOF) {
        frequency[byte]++;
    }
}

void print_first_header_bytes(unsigned char *first_header_bytes, long long int huffman_tree_size, int trash_size, FILE *compressed_file) {
    int i = 1;
    unsigned char bit_count;
    for (bit_count = 0; huffman_tree_size >= 1; ++bit_count) {
        if (bit_count == 8) {
            --i;
            bit_count = 0;
        }
        if (huffman_tree_size & 1) {
            first_header_bytes[i] = set_bit(bit_count, first_header_bytes[i]);
        }
        huffman_tree_size /= 2;
    }
    trash_size = 8 - (trash_size % 8);
    first_header_bytes[0] |= trash_size;
    // TODO still hasn't been tested
    fprintf(compressed_file, "%c%c", first_header_bytes[0], first_header_bytes[1]);
}

int compress(FILE *file) {
    long long int frequency[256] = {0}, i, j = 0;
    compose_frequency_array(frequency, file);

    HEAP *queue = create_heap();
    unsigned char key;
    printf("\nQueueing the nodes!\n");
    for (i = 0; i < 256; ++i) {
        key = (unsigned char)i;
        if (frequency[i]) {
            HUFF_NODE *hn = create_huff_node(frequency[i], key, NULL, NULL);
            enqueue(queue, hn);
        }
    }

    printf("Done!\n\nHere's the queue:\n");
    print_heap(queue);
    printf("\nCreating the tree\n");

    HUFF_NODE *root_node = build_tree(queue);

    printf("\nDone creating the tree, here's the tree pre-order traversal:\n");
    print_huff_tree(root_node);
    printf("\n\nAcquiring huffman tree size!\n");

    long long int huffman_tree_size = 0;
    get_huff_tree_size(root_node, &huffman_tree_size);
    
    printf("Done! And here's the size: %lld!\n", huffman_tree_size);
    printf("\nFreeing the queue!\n");
    
    free(queue);
    
    printf("Done!\n\nGenerating new mapping!\n");
    
    FILE *compressed_file = fopen("compressed.huff", "wb");
    int trash_size = 0;
    HASH_TABLE *mapping = generate_new_mapping(root_node, compressed_file, &trash_size);
    trash_size = 8 - (trash_size % 8);
    printf("Trash size: %d\n", trash_size);
    printf("Done!\n\n");
    
    unsigned char first_header_bytes[2] = {0};
    print_first_header_bytes(first_header_bytes, huffman_tree_size, trash_size, compressed_file);
    // printf("New mapping created! Heres the new mapping: \n");
    // print_hash_table(mapping);
    fclose(compressed_file);
}