HUFF = huff_tree/huff_tree.h huff_tree/huff_tree.c
HEAP = heap/heap.h heap/heap.c
HASH = hash/hash.h hash/hash.c
HEADER = header/header.h header/header.c
MAIN = main.c
TESTS = test/tests.c
COMPRESSOR = compressor/compressor.h compressor/compressor.c
DECOMPRESSOR = decompressor/decompressor.h decompressor/decompressor.c

compile_huff:
	gcc $(HUFF) $(HEAP) $(HASH) $(HEADER) $(MAIN) $(COMPRESSOR) $(DECOMPRESSOR) -o huffman -lm
compile_tests:
	gcc $(HUFF) $(HEAP) $(HASH) $(HEADER) $(TESTS) -o tests -lm -lcunit