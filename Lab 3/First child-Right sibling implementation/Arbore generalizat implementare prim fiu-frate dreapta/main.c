#include <stdio.h>
#include <stdlib.h>
#include "Arbore.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		perror(argc);
		exit(-1);
	}

	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		perror(argv[1]);
		exit(-1);
	}

	TTree arbore = InitTree(arbore);
	TKey cheie;
	TNodeRef primFiu, frateDreapta;

	while (fscanf("%hhu %hhu %hhu", &cheie, &primFiu, &frateDreapta) == 3)
		arbore = InsertNode(arbore, primFiu, frateDreapta, cheie);

	printArray(arbore);

	if (getRoot(arbore) != 0)
		preordine(arbore, 1);

	if (fclose(file) != 0){
		perror(NULL);
		exit(-1);
	}

	return 0;
}