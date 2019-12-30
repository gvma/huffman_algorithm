#include "CUnit/CUnit.h"
#include "../heap/heap.h"

HEAP *queue = NULL;

int diff(int a, int b) {
    return a - b;
}

int sum(int a, int b) {
    return a + b;
}

int init_suite(void) {
    return 0;
}

int clean_suite(void) { 
    return 0; 
}

void test_create_heap() {
    queue = create_heap();
    CU_ASSERT_NOT_EQUAL(NULL, queue);
    CU_ASSERT(0 == queue->size);
}

void test_enqueue() {
    HUFF_NODE *huff_node1 = create_huff_node(10, 'A', NULL, NULL);
    enqueue(queue, huff_node1);
    CU_ASSERT_NOT_EQUAL(NULL, queue->data[1]);
    CU_ASSERT(huff_node1 == queue->data[1]);
    CU_ASSERT_EQUAL(huff_node1->key, queue->data[1]->key);
    CU_ASSERT_EQUAL(huff_node1->frequency, queue->data[1]->frequency);
    CU_ASSERT_EQUAL(1, queue->size);
    CU_ASSERT_EQUAL(NULL, queue->data[1]->left);
    CU_ASSERT_EQUAL(NULL, queue->data[1]->right);
    HUFF_NODE *huff_node2 = create_huff_node(0, 'H', huff_node1, huff_node1);
    enqueue(queue, huff_node2);
    CU_ASSERT_NOT_EQUAL(NULL, queue->data[1]);
    CU_ASSERT(huff_node2 == queue->data[1]);
    CU_ASSERT_EQUAL(huff_node2, queue->data[1]);
    CU_ASSERT_EQUAL(huff_node2->key, queue->data[1]->key);
    CU_ASSERT_EQUAL(huff_node2->frequency, queue->data[1]->frequency);
    CU_ASSERT_EQUAL(2, queue->size);
    CU_ASSERT(queue->data[1]->left != NULL);
    CU_ASSERT_EQUAL(huff_node1, queue->data[1]->left);
    CU_ASSERT_EQUAL(huff_node1, queue->data[1]->right);
    huff_node1->frequency = 100000;
    enqueue(queue, huff_node1);
    CU_ASSERT_EQUAL(100000, queue->data[3]->frequency);
}

void test_dequeue() {
    HUFF_NODE *dequeued = queue->data[1];
    CU_ASSERT_EQUAL(dequeued, dequeue(queue));
    dequeued = queue->data[1];
    CU_ASSERT_EQUAL(dequeued, dequeue(queue));
    dequeued = queue->data[1];
    CU_ASSERT_EQUAL(dequeued, dequeue(queue));
    CU_ASSERT_PTR_NULL(dequeue(queue));
}

int main (void) {

    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("Basic_Test_Suite1", init_suite, clean_suite);
    
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "\n\n... Testing Heap Creation...\n\n", test_create_heap)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "\n\n... Testing Heap Enqueue...\n\n", test_enqueue)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "\n\n... Testing Heap Dequeue...\n\n", test_dequeue)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}