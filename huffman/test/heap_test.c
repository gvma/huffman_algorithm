#include "CUnit/CUnit.h"
#include "../heap/heap.h"

HEAP *heap = NULL;

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
    heap = create_heap();
    CU_ASSERT_NOT_EQUAL(NULL, heap);
    CU_ASSERT(0 == heap->size);
}

void test_enqueue() {
    HUFF_NODE *huff_node1 = create_huff_node(10, 'A', NULL, NULL);
    enqueue(heap, huff_node1);
    CU_ASSERT_NOT_EQUAL(NULL, heap->data[1]);
    CU_ASSERT(huff_node1 == heap->data[1]);
    CU_ASSERT_EQUAL(huff_node1->key, heap->data[1]->key);
    CU_ASSERT_EQUAL(huff_node1->frequency, heap->data[1]->frequency);
    CU_ASSERT_EQUAL(1, heap->size);
    CU_ASSERT_EQUAL(NULL, heap->data[1]->left);
    CU_ASSERT_EQUAL(NULL, heap->data[1]->right);
    CU_ASSERT_EQUAL(NULL, heap->data[1]->next);
    HUFF_NODE *huff_node2 = create_huff_node(0, 'H', huff_node1, huff_node1);
    enqueue(heap, huff_node2);
    CU_ASSERT_NOT_EQUAL(NULL, heap->data[2]);
    CU_ASSERT(huff_node2 == heap->data[2]);
    CU_ASSERT_EQUAL(huff_node2, heap->data[2]);
    CU_ASSERT_EQUAL(huff_node2->key, heap->data[2]->key);
    CU_ASSERT_EQUAL(huff_node2->frequency, heap->data[2]->frequency);
    CU_ASSERT_EQUAL(2, heap->size);
    CU_ASSERT(heap->data[2]->left != NULL);
    CU_ASSERT_EQUAL(huff_node1, heap->data[2]->left);
    CU_ASSERT_EQUAL(huff_node1, heap->data[2]->right);
    CU_ASSERT_NOT_EQUAL(huff_node1, heap->data[2]->next);
    huff_node1->frequency = 100000;
    enqueue(heap, huff_node1);
    CU_ASSERT_EQUAL(100000, heap->data[1]->frequency);
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

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}