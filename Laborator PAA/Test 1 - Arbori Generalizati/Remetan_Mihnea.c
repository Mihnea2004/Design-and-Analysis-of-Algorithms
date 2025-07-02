#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "ArboreGen.h"
#include <stdint.h>
#include <stdlib.h>

TNodeRef getRoot(TTree a) {
	if (a.size < 1) 
		return 0;

	return 1;
}

void preordine(TTree arbore, TNodeRef radacina) {
	printf("%d ", arbore.nodes[radacina].key);

	TNodeRef fc = firstChild(arbore, radacina);
	if (fc != 0)
		preordine(arbore, fc);

	TNodeRef rs = fc;
	while ((rs = rightSibling(arbore, rs)) != 0)
		preordine(arbore, rs);
}

void inordine(TTree arbore, TNodeRef radacina) {
	TNodeRef fc = firstChild(arbore, radacina);
	if (fc != 0)
		inordine(arbore, fc);

	printf("%d ", arbore.nodes[radacina].key);

	TNodeRef rs = fc;
	while ((rs = rightSibling(arbore, rs)) != 0)
		inordine(arbore, rs);
}

void postordine(TTree arbore, TNodeRef radacina) {
	TNodeRef fc = firstChild(arbore, radacina);
	if (fc != 0)
		postordine(arbore, fc);

	TNodeRef rs = fc;
	while ((rs = rightSibling(arbore, rs)) != 0)
		postordine(arbore, rs);

	printf("%d ", arbore.nodes[radacina].key);
}

//printNode(nodeByRef(arbore, radacina), " ");

int main(int argc, char* argv[]) {
	if (argc != 3) {
		perror(argc);
		exit(-1);
	}

	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		perror(argv[1]);
		exit(-1);
	}

	TTree arbore = { 0 };
	uint8_t parinte = 0, fiu = 0;
	
	while (fscanf(file, "%hhu %hhu", &parinte, &fiu) == 2) {
		arbore = InsertNode(arbore, parinte, fiu);
	}

	if (strcmp(argv[2], "A") == 0) {
		for (int i = 1; i <= arbore.size; i++) {
			printf("%hhd %hhd %hhd, ", arbore.nodes[i].key, arbore.nodes[i].firstChild, arbore.nodes[i].rightSibling); //afisare conform cerintei
		}
	} 
	else if (strcmp(argv[2], "P") == 0) {
		if (getRoot(arbore) != 0)
			preordine(arbore, 1);
	}
	else if (strcmp(argv[2], "I") == 0) {
		if (getRoot(arbore) != 0)
			inordine(arbore, 1);
	}
	else if (strcmp(argv[2], "O") == 0) {
		if (getRoot(arbore) != 0)
			postordine(arbore, 1);
	}

	if (fclose(file) != 0) {
		perror(NULL);
		exit(-1);
	}

	return 0;
}