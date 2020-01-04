#include "CUnit/CUnit.h"
#include "../heap/heap.h"
#include "../huff_tree/huff_tree.h"
#include "../hash/hash.h"

HEAP *queue = NULL;
HUFF_NODE *root = NULL;
HASH_TABLE *mapping = NULL;
const char tree_string[11] = "**CB**D*FEA";

int init_suite(void) {
    return 0;
}

int clean_suite(void) { 
    return 0; 
}

int get_leaves_quantity(HUFF_NODE *tree) {
    if (tree) {
        if (is_leaf(tree)) {
            return 1;
        }
        return get_leaves_quantity(tree->left) + get_leaves_quantity(tree->right);
    }
    return 0;
}

void compare_tree(HUFF_NODE *tree, long long int *pos)  {
    if (tree) {
        CU_ASSERT_EQUAL(tree_string[*pos], tree->key);
        *pos += 1;
        compare_tree(tree->left, pos);
        compare_tree(tree->right, pos);
    }
}

short int byte_to_short(unsigned char first_byte, unsigned char second_byte) {
    short int aux = first_byte;
    aux <<= 8;
    aux |= second_byte;
    return aux;
}

void test_new_hash_mapping() {
    int trash_size = 0;
    mapping = generate_new_mapping(root, &trash_size);
    CU_ASSERT_EQUAL(2, mapping->new_mapping['A'][0]);
    CU_ASSERT_EQUAL(2, mapping->new_mapping['B'][0]);
    CU_ASSERT_EQUAL(2, mapping->new_mapping['C'][0]);
    CU_ASSERT_EQUAL(3, mapping->new_mapping['D'][0]);
    CU_ASSERT_EQUAL(4, mapping->new_mapping['E'][0]);
    CU_ASSERT_EQUAL(4, mapping->new_mapping['F'][0]);
    CU_ASSERT_EQUAL(3, byte_to_short(mapping->new_mapping['A'][1], mapping->new_mapping['A'][2]));
    CU_ASSERT_EQUAL(1, byte_to_short(mapping->new_mapping['B'][1], mapping->new_mapping['B'][2]));
    CU_ASSERT_EQUAL(0, byte_to_short(mapping->new_mapping['C'][1], mapping->new_mapping['C'][2]));
    CU_ASSERT_EQUAL(4, byte_to_short(mapping->new_mapping['D'][1], mapping->new_mapping['D'][2]));
    CU_ASSERT_EQUAL(11, byte_to_short(mapping->new_mapping['E'][1], mapping->new_mapping['E'][2]));
    CU_ASSERT_EQUAL(10, byte_to_short(mapping->new_mapping['F'][1], mapping->new_mapping['F'][2]));
    CU_ASSERT_EQUAL(5, 8 - (trash_size % 8));
}

void test_tree_building() {
    queue = create_heap();
    enqueue(queue, create_huff_node(6, 'A', NULL, NULL));
    enqueue(queue, create_huff_node(5, 'B', NULL, NULL));
    enqueue(queue, create_huff_node(4, 'C', NULL, NULL));
    enqueue(queue, create_huff_node(3, 'D', NULL, NULL));
    enqueue(queue, create_huff_node(2, 'E', NULL, NULL));
    enqueue(queue, create_huff_node(1, 'F', NULL, NULL));
    root = build_tree(queue);
    long long int pos = 0;
    compare_tree(root, &pos);
    CU_ASSERT_EQUAL(strlen(tree_string), pos);
    pos = 0;
    get_huff_tree_size(root, &pos);
    CU_ASSERT_EQUAL(strlen(tree_string), pos);
    int leaves_quantity = 6;
    int var = get_leaves_quantity(root);
    CU_ASSERT_EQUAL(leaves_quantity, get_leaves_quantity(root));
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

    if ((NULL == CU_add_test(pSuite, "\n\n... Testing Heap Creation...\n\n", test_create_heap))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "\n\n... Testing Heap Enqueue...\n\n", test_enqueue))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "\n\n... Testing Heap Dequeue...\n\n", test_dequeue))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "\n\n... Testing Tree Building...\n\n", test_tree_building))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "\n\n... Testing New Hash Mapping...\n\n", test_new_hash_mapping))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}