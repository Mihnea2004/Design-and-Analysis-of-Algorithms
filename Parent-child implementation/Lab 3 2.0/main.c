#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "ArboreGen.h"

int main(int argc, char* argv[]) {
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		perror(argv[1]);
		exit(-1);
	}

	TTree arbore = { 0, 0 };
	arbore = InitTree(arbore);

	TNodeRef parinte;
	TKey cheie;

	while (fscanf(file, "%hhu %hhu", &cheie, &parinte) == 2) {
		printf("%hhu %hhu", cheie, parinte);
		arbore = InsertNode(arbore, parinte, cheie);
	}

	printArray(arbore);

	printf("\nPreordine\n");
	if (getRoot(arbore) != 0)
		preordine(arbore, 1);

	printf("\nInordine\n");
	if (getRoot(arbore) != 0)
		inordine(arbore, 1);

	printf("\nPostordine\n");
	if (getRoot(arbore) != 0)
		postordine(arbore, 1);

	if (fclose(file) != 0) {
		perror(NULL);
		exit(-1);
	}
	return 0;
}