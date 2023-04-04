compressor: main.c Huffman_Node.c MinHeap.c HeaderMap.c Huffman.c Encode.c 
	@cc main.c Huffman_Node.c MinHeap.c HeaderMap.c Huffman.c Encode.c -o compressor 

clean:
	@rm -f compressor 
	@rm -f  ./test/picture2.code
	@rm -f ./test/picture1.code
	@rm -f ./test/LoremIpsum.code
