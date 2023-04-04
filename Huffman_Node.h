#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H


/* The structure is responsible for storing the node.*/

typedef struct Node {
    int data;
    int freq;
    char *arr;
    struct Node* left;
    struct Node* right;
} node;

node * createNewNode(int,int ,node*,node*);

void free_node(node*);
#endif