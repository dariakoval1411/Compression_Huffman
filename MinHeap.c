#include "MinHeap.h"
#include "Huffman_Node.h"
#include <stdlib.h>

minheap * createMinHeap(int capacity){

    minheap *newHeap=malloc(sizeof(newHeap));
    if(newHeap==NULL)
        return NULL;
    
    newHeap->nodes=malloc(sizeof(minheap*) * capacity);
    if(newHeap->nodes==NULL)
        return NULL;
    
    newHeap->capacity=capacity;
    newHeap->size=0;

    return newHeap;
}

int double_node_capacity(minheap* array){
    array->capacity *=2;
    array->nodes=realloc(array->nodes,sizeof(node*) * array->capacity);
    if(array->nodes==NULL)
        return 1;

    return 0;
}

int add_node(minheap *array,node *node){
    if(array->size >= array->capacity)
        if(double_node_capacity(array)==1)
            return 1;
    
    array->nodes[array->size++]=node;

    return 0;
}

void freeMinHeap(minheap *array){
    free(array->nodes);
    free(array);

}