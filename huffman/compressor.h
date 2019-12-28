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
    long long int frequency[256] = {0}, j = 0;
    int i = 0;
    compose_frequency_array(frequency, file);
    HEAP *queue = create_heap();
    unsigned char *key = NULL;
    for (i = 0; i < 256; ++i) {
        if (frequency[i]) {
            key = ((unsigned char *)&i);
            printf("aqui na compress %c\n", (char) i);
            enqueue(queue, create_huff_node(frequency[i], key, NULL, NULL));
            print_heap(queue);
        }
    }
}

#endif