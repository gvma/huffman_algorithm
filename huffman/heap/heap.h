#ifndef heap_h
#define heap_h

#include "../header/header.h"
#include "../huff_tree/huff_tree.h"

typedef struct heap HEAP;

struct heap {
    HUFF_NODE *data[257]; // an array that will store all elements of the heap
    int size; //the size of the heap
};

/** @param queue: a pointer to the queue */
/** @param i: the index that you currently are in the queue */
/** @return returns the parent node of the queue */
int get_parent_index(HEAP *queue, int i);

/** @param queue: a pointer to the queue */
/** @param i: the index that you currently are in the queue */
/** @return returns the left child node of the queue */
int get_left_index(HEAP *queue, int i);

/** @param queue: the queue */
/** @param i: the index that you currently are in the queue */
/** @return returns the right child node of the queue */
int get_right_index(HEAP *queue, int i);

/** @param queue: a pointer to the queue */
/** @param i: the index that you currently are in the queue */
/** @return returns the i-th item of the queue */
HUFF_NODE *item_of(HEAP *queue, int i);

/** @param queue: a pointer to the queue */
/** @return returns if the queue is empty or not */
bool is_empty(HEAP *queue);

/** @return returns a new pointer to the heap */
HEAP *create_heap();

/** @param x: a pointer to the data of a type long long int*/
/** @param y: a pointer to the data of a type long long int*/
void swap(HUFF_NODE **x, HUFF_NODE **y);

/** @param queue: the queue */
/** @param i: the index that you currently are in the queue */
void min_heapify(HEAP *queue, int i);

/** @param queue: the queue */
void print_heap(HEAP *queue);

/** @param queue: the queue */
/** @return return the item that was in queue root */
HUFF_NODE *dequeue(HEAP *queue);

/** @param queue: a pointer to the queue */
/** @param item: an item that you want to enqueue in the queue*/
void enqueue(HEAP *queue, HUFF_NODE *item);


#endif