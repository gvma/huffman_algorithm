#ifndef compressor_h
#define compressor_H

#include "header/header.h"
#include "heap/heap.h"
#include "huff_tree/huff_tree.h"

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
    for (i = 0; i < 256; ++i) {
        unsigned char key = (unsigned char)i;
        if (frequency[i]) {
            HUFF_NODE *hn = create_huff_node(frequency[i], key, NULL, NULL);
            printf("KEY ANTES DA ENQUEUE: %c\n", *(unsigned char *)hn->key);
            enqueue(queue, hn);
            printf("KEY DEPOIS DA ENQUEUE: %c\n", *(unsigned char *)hn->key);
            printf("Apos chamada da enqueue:\n");
            print_heap(queue);
        }
    }
}

#endif