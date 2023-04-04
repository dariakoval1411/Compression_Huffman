#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Huffman.h"
#include "Encode.h"
#include "MinHeap.h"
#include "HeaderMap.h"

#define BYTE_SIZE 256

void help(){
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("\t\tThe program compresses files using the Huffman algorithm.\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("\tCompression creates a file with the extension .code containing the compressed dat.\n\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("Syntax: ./compressor [-f PLIK] [-s] [-h] \n\n");
    printf("Options:\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("\t-f\tThe path of the file to be compressed\n");
    printf("\t-s\tDisplay of the file size before and after compression\n");
    printf("\t-h\tDisplays the help window(help)\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("The program can compress several files at once.\n");
    printf("Then you need to put an option in front of the path of each file -f.\n");
    printf("\tExample: ./compressor -f file1 -f file2 -f file3\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}
long int get_file_size(FILE* f){

    fseek(f,0L,SEEK_END);
    long int file_size=ftell(f);

    return file_size/1024;
}

double get_size(FILE* f){

    fseek(f,0L,SEEK_END);
    double  file_size=ftell(f);

    return file_size;
}

int main(int argc,char **argv){

    int i, j;				               // Variables to iterate over

	// getopt variables
	char opt;				             // A variable that specifies the getopt option
	header *files = createHeader(2); 	// The vector holds the names of the files to be compressed
	int show_file_size = 0;			   // Option to display size before and after compression

	// Reading files for compression
	FILE *in; 				          // input file
	int freq[BYTE_SIZE]; 			// The frequency of bytes in the file
	int byte; 				        // Holds values ​​<0; 255>

	// Creating a tree
	minheap *nodes; 			// Node vector (no codes)
	node *root; 				// Tree root

	// Encoding to a file
	minheap *codes; 			     // It stores nodes with codes
	char temp_code[BYTE_SIZE]; 		// A temporary string of characters needed to generate codes
	char *file_ext; 			   // Original file extension
	int file_name_n;			  // The length of the original filename without the extension
	char *file_name;			 // The name of the original file without the extension
	char *out_file_name;		 //The name of the compressed output file
	FILE *out_file;				// Output compressed file
	
	// Loading options from getopt
	while ((opt = getopt(argc, argv, "hsf:")) != -1){
    		switch (opt){
	      		case 'f':
				// Adding a new file to the compression
        			if (add_header(files, optarg) == 1){
					fprintf(stderr, "%s: File name memory allocation error: %s\n", argv[0], files->name[j]);
					return 3;
				}
        			break;
	      		case 's':
				// Option to display file size before and after compression
				show_file_size = 1;
				break;
	      		case 'h':
				// Help window
				help();
				return 0;
  	    		case '?':
				help();
				return 4;
		}
	}

	if (files->size < 1)
	{
		fprintf(stderr, "%s: No file specified.\n\n", argv[0]);
		help();
		return 1;
	}

	// Iterating over the files to be compressed
	for (j = 0; j < files->size; j++){	
		// Opening a file
		in = fopen(files->name[j], "rb");
		if (in == NULL){
			fprintf(stderr, "%s: File read error: %s\n", argv[0], files->name[j]);
			return 1;
		}
		
		// Resetting the byte frequency for the file
		for (i = 0; i < BYTE_SIZE; i++)
			freq[i] = 0;
		
		// Counting character frequencies
		while ((byte = fgetc(in)) != EOF)
			freq[byte]++;
		
		fclose(in);

		// Creating node structures
		nodes = createMinHeap(8);
		if (nodes == NULL){
			fprintf(stderr, "%s: Node structure memory allocation error: %s\n", argv[0], files->name[j]);
			return 3;
		}

		for (i = 0; i < BYTE_SIZE; i++){
			if(freq[i] != 0){
				if (add_node(nodes, createNewNode(i, freq[i], NULL, NULL)) == 1){
					fprintf(stderr, "%s: Node memory allocation error: %s\n", argv[0], files->name[j]);
					return 3;
				}
			}
		}
		
		// Adding a node with end-of-file (-1)
		if (add_node(nodes, createNewNode(-1, 1, NULL, NULL)) == 1){
			fprintf(stderr, "%s: Terminal node memory allocation error: %s\n", argv[0], files->name[j]);
			return 3;
		}

		// Creating a tree
		root = buildHuffmanTree(nodes);
		if (root == NULL){
			fprintf(stderr, "%s: Tree memory allocation error: %s\n", argv[0], files->name[j]);
			return 3;
		}

		// Reading codes from the tree
		codes = createMinHeap(8);
		if (codes == NULL){
			fprintf(stderr, "%s: Node structure memory allocation error with codes: %s\n", argv[0], files->name[j]);
			return 3;
		}

		temp_code[0] = '\0';
		read_codes(root, codes, temp_code);

		for (i = 0; i < codes->size; i++){
			if (codes->nodes[i]->arr == NULL){
				fprintf(stderr, "%s: Code memory allocation error: %s\n", argv[0], files->name[j]);
				return 3;
			}
		}

		// Reading the extension of the original file
		file_ext = strrchr(files->name[j], '.');
		if (file_ext != NULL) {
			file_ext++;
			if ((file_ext - 1) - strrchr(files->name[j], '/') < 0)
				// We check if the found dot belongs to the filename itself and not to the path
				file_ext = NULL;
		}
			
		// Counting the length of the original file name (without extension)
		if (file_ext != NULL)
			file_name_n = strlen(files->name[j]) - strlen(file_ext) - 1;
		else
			file_name_n = strlen(files->name[j]);
		
		// Saving the file name without extension
		file_name = malloc(sizeof(char) * (file_name_n + 1));
		if (file_name == NULL){
			fprintf(stderr, "%s: File name memory allocation error: %s\n", argv[0], files->name[j]);
			return 3;
		}

		for (i = 0; i < file_name_n; i++)
			file_name[i] = files->name[j][i];
		file_name[i] = '\0';
		
		// Create output filenames
		out_file_name = malloc(sizeof(char) * (file_name_n + 5));
		if (out_file_name == NULL){
			fprintf(stderr, "%s: Output file name memory allocation error: %s\n", argv[0], files->name[j]);
			return 3;
		}
		
		strcpy(out_file_name, file_name);
		strcat(out_file_name, ".code\0");
				
		// File encoding
		in = fopen(files->name[j], "rb");
		if (in == NULL){
			fprintf(stderr, "%s: File read error: %s\n", argv[0], files->name[j]);
			return 1;
		}

		out_file = fopen(out_file_name, "wb");
		if (out_file == NULL){
			fprintf(stderr, "%s: No file permissions: %s\n", argv[0], files->name[j]);
			return 2;
		}

		encode(in, out_file, file_ext, codes);
	
		// Displaying file size before and after compression (call option)
		if (show_file_size){
			printf("%s\n", files->name[j]);
			printf("\tSize before compression ---->%ld [KB]\n", get_file_size(in));
			printf("\tCompressed size -----> %ld [KB]\n", get_file_size(out_file));
            printf("\tSize before compression ---->%g \n", get_size(in));
			printf("\tCompressed size -----> %g \n", get_size(out_file));
            double ratio=(double)get_size(in)/(double)get_size(out_file);
            printf("\tCompression ratio  -----> %g \n", ratio);
		}

		fclose(in);
		fclose(out_file);

		// Freeing memory so the next file can be overwritten
		free(file_name);
		free(out_file_name);
		freeMinHeap(nodes);
		
		for (i = 0; i < codes->size; i++)
			free_node(codes->nodes[i]);
		freeMinHeap(codes);
		
		free_HuffmanTree(root);
	}	
	
	free_header(files);
		
	return 0;
}