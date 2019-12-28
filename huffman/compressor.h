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
        if (frequency[i]) {
            printf("aqui na compress %c\n", (char) i);
            HUFF_NODE *new_huff_node = create_huff_node(frequency[i], &i, NULL, NULL);
            enqueue(queue, new_huff_node);
        }
    }
    print_heap(queue);
    printf("%c\n", *(unsigned char *)dequeue(queue)->key);
    printf("%c\n", *(unsigned char *)dequeue(queue)->key);
    printf("%c\n", *(unsigned char *)dequeue(queue)->key);
    printf("%c\n", *(unsigned char *)dequeue(queue)->key);
    printf("%c\n", *(unsigned char *)dequeue(queue)->key);
    printf("%c\n", *(unsigned char *)dequeue(queue)->key);
}

#endif