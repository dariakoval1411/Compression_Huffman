#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "Huffman_Node.h"
#include "MinHeap.h"

int node_compare(const void *,const void *);
node * buildHuffmanTree(minheap *);
void read_codes(node*,minheap*,char*);
void free_HuffmanTree(node*);


#endif 
