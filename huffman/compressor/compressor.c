#include "compressor.h"

void print_byte(unsigned char byte, char *msg) {
    printf("%s: ", msg);
    int i;
    for (i = 7; i >= 0; --i) {
        printf("%d", is_bit_i_set(byte, i));
    }
    printf("\n");
}

void compress(FILE *file, FILE *compressed_file, HASH_TABLE *mapping, int trash_size) {
    int i = 0, compressed_length = 0, bit_position = 0, compressed_byte = 0;
    unsigned char byte;
    while (fscanf(file, "%c", &byte) != EOF) {
        compressed_length = mapping->new_mapping[byte][0];
        for (i = compressed_length - 1; i >= 0; --i) {
            if (i > 7) {
                if (is_bit_i_set(mapping->new_mapping[byte][1], i % 8)) {
                    ++compressed_byte;
                }
            } else {
                if (is_bit_i_set(mapping->new_mapping[byte][2], i)) {
                    ++compressed_byte;
                }
            }
            if (bit_position == 7) {
                bit_position = -1;
                fprintf(compressed_file, "%c", compressed_byte);
                compressed_byte = 0;
            }
            ++bit_position;
            compressed_byte <<= 1;
        }
    }
    compressed_byte >>= 1;
    compressed_byte <<= trash_size;
    fprintf(compressed_file, "%c", compressed_byte);
}

void compose_frequency_array(long long int *frequency, FILE *file) {
    unsigned char byte;
    while (fscanf(file, "%c", &byte) != EOF) {
        frequency[byte]++;
    }
}

void print_first_header_bytes(unsigned char *first_header_bytes, long long int huffman_tree_size, int trash_size, FILE *compressed_file) {
    short int first_two = trash_size;
    first_two <<= 13;
    first_two += huffman_tree_size;
    fprintf(compressed_file, "%c%c", first_two >> 8, first_two);
}

void compression(FILE *file, char *file_path) {
    long long int frequency[256] = {0}, i, j = 0;
    compose_frequency_array(frequency, file);

    HEAP *queue = create_heap();
    unsigned char key;
    printf("\nQueueing the nodes!\n");
    for (i = 0; i < 256; ++i) {
        key = (unsigned char)i;
        if (frequency[i]) {
            HUFF_NODE *hn = create_huff_node(frequency[i], key, NULL, NULL);
            enqueue(queue, hn);
        }
    }

    printf("Done!\n\nHere's the queue:\n");
    print_heap(queue);
    printf("\nCreating the tree...\n");

    HUFF_NODE *root_node = build_tree(queue);

    printf("\nDone creating the tree!\n");
    printf("\n\nAcquiring huffman tree size!\n");

    long long int huffman_tree_size = 0;
    get_huff_tree_size(root_node, &huffman_tree_size);
    
    printf("Done! And here's the size: %lld!\n", huffman_tree_size);
    printf("\nFreeing the queue!\n");
    
    free(queue);
    
    printf("Done!\n\nGenerating new mapping!\n");
    
    char extension[5] = ".huff";
    strcat(file_path, extension);


    FILE *compressed_file = fopen(file_path, "w");
    int trash_size = 0;
    HASH_TABLE *mapping = generate_new_mapping(root_node, &trash_size);
    trash_size = 8 - (trash_size % 8);
    if (trash_size == 8) {
        trash_size = 0;
    }
    printf("Trash size: %d\n", trash_size);
    printf("Done!\n\n");
    unsigned char first_header_bytes[2] = {0};
    print_first_header_bytes(first_header_bytes, huffman_tree_size, trash_size, compressed_file);
    printf("Printing the pre-order traversal of the tree!\n");
    print_huff_tree(root_node, compressed_file);
    rewind(file);
    compress(file, compressed_file, mapping, trash_size);
    fclose(compressed_file);
}