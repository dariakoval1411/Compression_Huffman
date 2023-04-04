#include "Huffman_Node.h"
#include <stdlib.h>

node * createNewNode(int data,int freq,node *left,node *right){
    node* newNode=malloc(sizeof(node));

    if(newNode==NULL)
        return NULL; // Memory allocation error
    
    newNode->data=data;
    newNode->freq=freq;
    newNode->arr=NULL;
    newNode->left=left;
    newNode->right=right;

    return newNode;
}

void free_node(node *temp){
    /* Free code memory.
    If the code == NULL, 
    the memory was not allocated and there is no need to use free. */
    if(temp->arr !=NULL)
        free(temp->arr);

    free(temp);    
}