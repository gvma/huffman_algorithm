#ifndef compressor_h
#define compressor_H

#include "header/header.h"
#include "huff_tree/huff_tree.h"
#include "hash/hash.h"
#include "heap/heap.h"

void compose_frequency_array(long long int *frequency, FILE *file) {
    unsigned char byte;
    while (fscanf(file, "%c", &byte) != EOF) {
        frequency[byte]++;
    }
}

int compress(FILE *file) {
    long long int frequency[256] = {0}, i, j = 0;
    compose_frequency_array(frequency, file);
    HEAP *queue = create_heap();
    unsigned char key;
    printf("Queueing the nodes!\n");
    for (i = 0; i < 256; ++i) {
        key = (unsigned char)i;
        if (frequency[i]) {
            HUFF_NODE *hn = create_huff_node(frequency[i], key, NULL, NULL);
            enqueue(queue, hn);
        }
    }
    printf("Done queueing, here's the queue:\n");
    print_heap(queue);
    printf("Creating the tree:\n");
    unsigned char root_char = '*';
    HUFF_NODE *root_node;
    while (queue->size != 1) {
        HUFF_NODE *left_child = dequeue(queue);
        HUFF_NODE *right_child = dequeue(queue);
        root_node = create_huff_node(left_child->frequency + right_child->frequency, root_char, left_child, right_child);
        enqueue(queue, root_node);
    }
    printf("Done creating the tree, here's the tree pre-order traversal:\n");
    print_huff_tree(root_node);
    printf("\n");
    printf("Freeing the queue!\n");
    free(queue);
    printf("Generating new mapping!\n");
    FILE *compressed_file = fopen("compressed.huff", "wb");
    generate_new_mapping(root_node, compressed_file);
}

#endif