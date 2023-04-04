#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MinHeap.h"
#include "Huffman_Node.h"


// The function compares two nodes for sign frequency.
int node_compare(const void *a, const void *b){
	return (*(node**)a)->freq - (*(node**)b)->freq;
}

// The function creates a Huffman tree structure and finally returns the root node of the tree.
node * buildHuffmanTree(minheap *array){
	int i;
	node *temp;

	qsort(array->nodes, array->size, sizeof(node*), node_compare);
	
	while (array->size > 1){
		//Connecting the first two nodes together
		array->nodes[0] = createNewNode(0, array->nodes[0]->freq + array->nodes[1]->freq, array->nodes[0], array->nodes[1]);

		if (array->nodes[0] == NULL)
			// Memory allocation error
			return NULL;

		// Uploading the rest of the nodes to fill the gap
		for (i = 1; i < array->size - 1; i++)
            		array->nodes[i] = array->nodes[i + 1];
		
		array->size--;
		
		// Moving the created node so that the vector is further sorted
		for (i = 0; i < array->size - 1 && (array->nodes[i])->freq > (array->nodes[i + 1])->freq; i++){
            		temp = array->nodes[i];
			array->nodes[i] = array->nodes[i + 1];
			array->nodes[i + 1] = temp;
		}
	}

	return array->nodes[0];
}


// The function moves through the Huffman tree and writes the characters and their codes to the node vector
void read_codes(node *root, minheap *codes, char *temp_code){
	char *tmp;

	if (root->left != NULL){
		strcat(temp_code, "0\0");
		read_codes(root->left, codes, temp_code);
	}

	if (root->right != NULL){
		strcat(temp_code, "1\0");
		read_codes(root->right, codes, temp_code);
	}

	if (root->left == NULL && root->right == NULL){
		/* Allocating memory for the string that holds the code
		 * The memory will be freed when the function freeing the entire node is called. */
		tmp = malloc(sizeof(char) * (strlen(temp_code) + 1));
		strcpy(tmp, temp_code);
		add_node(codes, createNewNode(root->data, root->freq, NULL, NULL));
		codes->nodes[codes->size - 1]->arr = tmp;
	}	

	if (strlen(temp_code) > 0)
		temp_code[strlen(temp_code) - 1] = '\0';
}


// Releases the nodes in the Huffman tree
void free_HuffmanTree(node *root){	
	if (root->left != NULL)
		free_HuffmanTree(root->left);		

	if (root->right != NULL)
		free_HuffmanTree(root->right);

	free_node(root);
}
