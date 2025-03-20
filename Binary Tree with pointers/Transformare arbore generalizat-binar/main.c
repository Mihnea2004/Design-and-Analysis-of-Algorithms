#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Arbore.h"

int main(int argc, char** argv) {
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		perror(argv[1]);
		exit(-1);
	}

	int valoare, parinte;
	Nod* radacina = NULL;

	while (fscanf(file, "%d, %d", &valoare, &parinte) == 2) {
		if (parinte = 0)
			radacina = creareNod(valoare);
		else
			adaugaNod(radacina, valoare, parinte);
	}

	preordine(radacina);

	if (fclose(file) != 0) {
		perror(NULL);
		exit(-1);
	}

	eliberareMemorie(radacina);

	return 0;
}