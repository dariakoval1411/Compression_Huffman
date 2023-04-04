#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MinHeap.h"


/* Searches for codes in the vector and returns the one that matches the given character */
char *find_code(int data, minheap *array){
    int i;
	for (i = 0; i < array->size; i++)
		if(array->nodes[i]->data == data)
			return array->nodes[i]->arr;
	
	return NULL;
}

/* A function that encodes characters into a file and creates a key file
 * We read the next bytes of the file, find the appropriate codes and then load them into the output file.
 * At the very end, load the end-of-file character (-1) and pad with zeros to a full byte if necessary. */
void encode(FILE *input, FILE *output, char* file_ext, minheap *array){
	char byte = 0;			 // The byte value that will be written to the output file.
	int shift = 0;			// The bit shift of the byte variable.
	char* code;			   //A pointer to the character code
	int i, c;			  //Variables to iterate over

	/* Write the extension of the original file as the first line.
    * First line empty if no extension ('\n' only)*/
	if (file_ext != NULL)
		fprintf(output, "%s\n", file_ext);
	else
		fprintf(output, "\n");
	
	// Writing characters and codes to a file.
	for (i = 0; i < array->size; i++)
		fprintf(output, "%d %s\n", array->nodes[i]->data, array->nodes[i]->arr);
	
	// The '\0' character indicates the end of the dictionary part
	fwrite(&byte, 1, sizeof(byte), output);

	// Load character codes to file
	while ((c = getc(input)) != EOF){
		// We look for the character code
		code = find_code(c, array);

		// We write bit by bit to the output file
		for (i = 0; i < strlen(code); i++){
			if (shift > 7){
				/* If shifted by 8 bits, write to file.
                * We clear the byte */
				fwrite(&byte, 1, sizeof(byte), output);
				byte = 0;
				shift = 0;
			}

			// Write bit to byte
			byte |= ((code[i] - '0') << (7 - shift));
			shift++;
		}
	}

	// Load the end character (-1) into the file
	code = find_code(-1, array);		
	for (i = 0; i < strlen(code); i++){
		if (shift > 7){
			fwrite(&byte, 1, sizeof(byte), output);
			byte = 0;
			shift = 0;
		}
		byte |= ((code[i] - '0') << (7 - shift));
		shift++;
	}
		
	// Zero pad if not full byte filled
	while (shift < 8){
		byte |= (0 << (7 - shift));
		shift++;
	}

	fwrite(&byte, 1, sizeof(byte), output);
}
