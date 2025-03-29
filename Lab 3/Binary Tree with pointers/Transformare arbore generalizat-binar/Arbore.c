#include <stdio.h>
#include <stdlib.h>
#include "Arbore.h"

typedef struct Nod{
	int valoare;
	struct Nod* stanga;
	struct Nod* dreapta;
}Nod;

Nod* creareNod(int valoare) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	if (nodNou == NULL) {
		perror(NULL);
		exit(-1);
	}

	nodNou->valoare = valoare;
	nodNou->stanga = NULL;
	nodNou->dreapta = NULL;

	return nodNou;
}

Nod* inserareNod(Nod* radacina, int valoare) {
	Nod* nodNou = creareNod(valoare);
	if (radacina == NULL)
		return nodNou;

	if (valoare < radacina->valoare)
		radacina->stanga = inserareNod(radacina->stanga, valoare);
	else
		radacina->dreapta = inserareNod(radacina->dreapta, valoare);

	return radacina;
}

void preordine(Nod* radacina) {
	if (radacina != NULL) {
		printf("%d ", radacina->valoare);
		preordine(radacina->stanga);
		preordine(radacina->dreapta);
	}
}

void eliberareMemorie(Nod* radacina) {
	if (radacina != NULL) {
		eliberareMemorie(radacina->stanga);
		eliberareMemorie(radacina->dreapta);
		free(radacina);
	}
}

void adaugaNod(Nod* radacina, int valoare, int parinte) {
	if (radacina == NULL)
		return;

	if (radacina->valoare == parinte) {
		if (valoare < parinte) {
			if (radacina->stanga == NULL)
				radacina->stanga = creareNod(valoare);
			else
				inserareNod(radacina -> stanga, valoare);
		}
		else {
			if (radacina->dreapta == NULL)
				radacina->dreapta = creareNod(valoare);
			else
				inserareNod(radacina->dreapta, valoare);
		}
	}
	else {
		adaugaNod(radacina->stanga, valoare, parinte);
		adaugaNod(radacina->dreapta, valoare, parinte);
	}
}