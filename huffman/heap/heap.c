#include "heap.h"

int get_parent_index(HEAP *queue, int i) {
    return i >> 1;
}

int get_left_index(HEAP *queue, int i) {
    return i << 1;
}

int get_right_index(HEAP *queue, int i) {
    return (i << 1) + 1;
}

HUFF_NODE *item_of(HEAP *queue, int i) {
    return queue->data[i];
}

bool is_empty(HEAP *queue) {
    return queue->size == 0;
}

HEAP *create_heap() {
    HEAP *new_heap = (HEAP*)malloc(sizeof(HEAP));
    int i;
    new_heap->size = 0;
    for (i = 0; i <= 256; ++i) {
        new_heap->data[i] = NULL;
    }
    return new_heap;
}

void swap(HUFF_NODE **x, HUFF_NODE **y) {
    HUFF_NODE *aux = *x;
    *x = *y;
    *y = aux;
}

void min_heapify(HEAP *queue, int i) {
    int biggest;
    int left_index = get_left_index(queue, i);
    int right_index = get_right_index(queue, i);

    if (left_index <= queue->size && queue->data[left_index]->frequency < queue->data[i]->frequency) {
        biggest = left_index;
    } else {
        biggest = i;
    }
    if (right_index <= queue->size && queue->data[right_index]->frequency < queue->data[biggest]->frequency) {
        biggest = right_index;
    }
    if (queue->data[i]->frequency != queue->data[biggest]->frequency) {
        swap(&queue->data[i], &queue->data[biggest]);
        min_heapify(queue, biggest);
    }
}

void print_heap(HEAP *queue) {
    int i;
    printf("Printando Fila: \n");
    for (i = 1; i <= queue->size; ++i) {
        printf("(%c, %lld) -> ", queue->data[i]->key, queue->data[i]->frequency);
    }
    printf("\n");
}

HUFF_NODE *dequeue(HEAP *queue) {
    if (is_empty(queue)) {
        printf("Heap Underflow! Cannot dequeue!\n");
        return NULL;
    } else {
        HUFF_NODE *item = queue->data[1];
        queue->data[1] = queue->data[queue->size];
        --queue->size;
        min_heapify(queue, 1);
        return item;
    }
}

void enqueue(HEAP *queue, HUFF_NODE *item) {
    if (queue->size >= 100000) {
        printf("Heap Overflow! Cannot enqueue!\n");
    } else {
        queue->data[++queue->size] = item;
        int key_index = queue->size;
        int parent_index = get_parent_index(queue, key_index);
        while (parent_index >= 1 && queue->data[key_index]->frequency < queue->data[parent_index]->frequency) {
            swap(&queue->data[key_index], &queue->data[parent_index]);
            printf("Ta entrando aqui dentro?\n");
            key_index = parent_index;
            parent_index = get_parent_index(queue, key_index);
        }
    }
}