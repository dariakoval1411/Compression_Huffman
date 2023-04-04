#ifndef MINHEAP_H
#define MINHEAP_H

#include "Huffman_Node.h"



//The structure of a dynamic vector storing pointers to nodes.

typedef struct Min_Heap{
    node **nodes;
    int size;
    int capacity;

} minheap;

minheap *createMinHeap(int);
int double_node_capacity(minheap*);
int add_node(minheap*,node*);
void freeMinHeap(minheap*);

#endif