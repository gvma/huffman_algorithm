#ifndef heap_h
#define heap_h

#include "../header/header.h"
#include "../huff_tree/huff_tree.h"

typedef struct heap HEAP;

struct heap {
    HUFF_NODE *data[257]; // an array that will store all elements of the heap
    int size; //the size of the heap
};

/** @param heap: a pointer to the heap */
/** @param i: the index that you currently are in the heap */
/** @return returns the parent node of the heap */
int get_parent_index(HEAP *heap, int i) {
    return i >> 1;
}

/** @param heap: a pointer to the heap */
/** @param i: the index that you currently are in the heap */
/** @return returns the left child node of the heap */
int get_left_index(HEAP *heap, int i) {
    return i << 1;
}

/** @param heap: the heap */
/** @param i: the index that you currently are in the heap */
/** @return returns the right child node of the heap */
int get_right_index(HEAP *heap, int i) {
    return (i << 1) + 1;
}

/** @param heap: a pointer to the heap */
/** @param i: the index that you currently are in the heap */
/** @return returns the i-th item of the heap */
HUFF_NODE *item_of(HEAP *heap, int i) {
    return heap->data[i];
}

/** @param heap: a pointer to the heap */
/** @return returns if the heap is empty or not */
bool is_empty(HEAP *heap) {
    return heap->size == 0;
}

/** @param sz: heap size */
/** @return returns a new pointer to the heap */
HEAP *create_heap() {
    HEAP *new_heap = (HEAP*)malloc(sizeof(HEAP));
    int i;
    for (i = 1; i <= 256; ++i) {
        new_heap->data[i] = NULL;
    }
    return new_heap;
}

/** @param x: a pointer to the data of a type long long int*/
/** @param y: a pointer to the data of a type long long int*/
void swap(HUFF_NODE **x, HUFF_NODE **y) {
    HUFF_NODE aux = **x;
    **x = **y;
    **y = aux;
}

/** @param heap: the heap */
/** @param i: the index that you currently are in the heap */
void max_heapify(HEAP *heap, int i) {
    int biggest;
    int left_index = get_left_index(heap, i);
    int right_index = get_right_index(heap, i);

    if (left_index <= heap->size && heap->data[left_index]->frequency > heap->data[i]->frequency) {
        biggest = left_index;
    } else {
        biggest = i;
    }
    if (right_index <= heap->size && heap->data[right_index]->frequency > heap->data[biggest]->frequency) {
        biggest = right_index;
    }
    if (heap->data[i]->frequency != heap->data[biggest]->frequency) {
        swap(&heap->data[i], &heap->data[biggest]);
        max_heapify(heap, biggest);
    }
}

void print_heap(HEAP *queue) {
    int i;
    printf("Printando Fila: \n");
    for (i = 1; i <= queue->size; ++i) {
        printf("(%c, %lld) -> ", *(unsigned char *)queue->data[i]->key, queue->data[i]->frequency);
    }
    printf("\n");
}

/** @param heap: the heap */
/** @return return the item that was in heap root */
HUFF_NODE *dequeue(HEAP *heap) {
    if (is_empty(heap)) {
        printf("Heap Underflow! Cannot dequeue!\n");
        return NULL;
    } else {
        HUFF_NODE *item = heap->data[1];
        heap->data[1] = heap->data[heap->size];
        --heap->size;
        max_heapify(heap, 1);
        return item;
    }
}

/** @param heap: a pointer to the heap */
/** @param item: an item that you want to enqueue in the heap*/
void enqueue(HEAP *heap, HUFF_NODE *item) {
    printf("Antes:\n");
    print_heap(heap);
    if (heap->size >= 100000) {
        printf("Heap Overflow! Cannot enqueue!\n");
    } else {
        heap->data[++heap->size] = item;
        int key_index = heap->size;
        int parent_index = get_parent_index(heap, key_index);
        if (parent_index) {
            printf("While Comparisons: %d %d\n", parent_index >= 1, heap->data[key_index]->frequency > heap->data[parent_index]->frequency);
        }
        printf("Depois:\n");
        print_heap(heap);
        while (parent_index >= 1 && heap->data[key_index]->frequency > heap->data[parent_index]->frequency) {
            printf("eu to entrando na swap????\n");
            swap(&heap->data[key_index], &heap->data[parent_index]);
            key_index = parent_index;
            parent_index = get_parent_index(heap, key_index);
        }
    }
}


#endif