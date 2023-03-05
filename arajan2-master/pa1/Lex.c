/********************************************************************************* 
* Anya Rajan
* 2022 Spring CSE101 PA1 
* Lex.c 
* Lex.c for to utilize List ADT functions 
**********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]) {
 
	int line_count;
   	FILE *in, *out;
   	char line[MAX_LEN];

	// check command line for correct number of arguments
	if (argc != 3) {
      		printf("Usage: %s <input file> <output file>\n", argv[0]);
      		exit(1);
   	}	

	// open files for reading and writing
	in = fopen(argv[1], "r");
      	if (in == NULL) {
      		printf("Unable to open file %s for reading\n", argv[1]);
      		exit(1);
   	}

	 out = fopen(argv[2], "w");
  	 if (out == NULL) {
      		printf("Unable to open file %s for writing\n", argv[2]);
      		exit(1);
   	 }

	line_count = 0;
   	while (fgets(line, MAX_LEN, in) != NULL)  {
      		line_count = line_count + 1;	
	}

	fclose(in);
	
	in = NULL;
	in = fopen(argv[1], "r");

	int counter = 0;
	char **array = calloc(line_count, sizeof(char*));	
	while (fgets(line, MAX_LEN, in) != NULL) {
		array[counter] = calloc(MAX_LEN, sizeof(char*)+1);
		strcpy(array[counter], line);
		counter = counter + 1;
	}

	List new = newList();
	append(new, 0);

	int i, j;
	// char store;
	
	for (i = 1; i < line_count; i++) {
		j = i - 1;
		if (length(new) > 0) {
			moveFront(new);
			while (index(new) != j) {
				moveNext(new);
			}
		}
		while (j >= 0 && strcmp(array[i], array[get(new)]) < 0) {
			movePrev(new);
			j = j - 1;
		}
		if (index(new) == - 1) {
			prepend(new, i);
		}
		else {
			insertAfter(new, i);
		}
	}	
	// print the array in alphabetical order TO OUT FILE--> so print the List? makes sense
	moveFront(new);
	for (int x = 0; x < line_count; x++) {
		fprintf(out, "%s\n", array[get(new)]);
		moveNext(new);
	}

	// FREE ALL MEMORY:
	// array
	// array elements
	// free list
	for (int x = 0; x < line_count; x++) {
		free(array[x]);
		// array[x] = NULL;
	} 

	free(array);
	array = NULL;

	freeList(&new);
	
	// close files
	fclose(in);
	fclose(out);
	return(0);
}
