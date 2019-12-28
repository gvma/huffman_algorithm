HUFF = huff_tree/huff_tree.h
HEAP = heap/heap.h
HASH = hash/hash.h
HEADER = header/header.h
MAIN = main.c
TESTS = test/heap_test.c
COMPRESSOR = compressor.h

compile_huff:
	gcc $(HUFF) $(HEAP) $(HASH) $(HEADER) $(MAIN) $(COMPRESSOR) -o huffman -lm
compile_tests:
	gcc $(HUFF) $(HEAP) $(HASH) $(HEADER) $(TESTS) -o tests -lm -lcunit