#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 20

// 5
// 0 1 2
// 0 3 6
// 1 2 3
// 1 3 8
// 1 4 5
// 2 4 7
// 3 4 9

int graf[SIZE][SIZE]; //matricea de adiacenta
int parinte[SIZE]; //parintii pt arborele minim
int key[SIZE]; //costul minim de a ajunge la fiecare nod
int set[SIZE]; //1 daca e pus nodul in MST, altfel 0
 
int readFromFile(char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		perror(NULL);
		exit(-1);
	}

	//nod1 nod2 cost
	int nrNoduri = 0;
	if (fscanf(file, "%d", &nrNoduri) != 1) {
		perror(NULL);
		exit(-1);
	}

	int a, b, c;
	while (fscanf(file, "%d %d %d", &a, &b, &c) == 3) {
		//se construieste matricea de adiacenta
		graf[a % nrNoduri][b % nrNoduri] = c;
		graf[b % nrNoduri][a % nrNoduri] = c;
	}

	if (fclose(file) != 0) {
		perror(NULL);
		exit(-1);
	}

	return nrNoduri;
}

int findMinimumCost(int key[], int set[], int nrNoduri) {
	int minCost = INT_MAX;
	int minIndex = -1;

	for (int i = 0; i < nrNoduri; i++) {
		if (set[i] == 0 && key[i] < minCost) { //cauta nodul neinclus in MST
			minCost = key[i];
			minIndex = i;
		}
	}

	return minIndex;
}

void printMinTree(int parinte[], int graf[SIZE][SIZE], int nrNoduri) {
	int minCost = 0;
	for (int i = 1; i < nrNoduri; i++) {
		printf("Muchia: %d - %d -> Cost: %d\n", parinte[i], i, graf[parinte[i]][i]);
		minCost += graf[parinte[i]][i];
	}
	printf("\nCostul minim este %d!\n", minCost);
}

void prim(int graf[SIZE][SIZE], int nrNoduri) {
	for (int i = 0; i < nrNoduri; i++) {
		key[i] = INT_MAX;
		set[i] = 0;
	}

	key[0] = 0;
	parinte[0] = -1;

	//se alege nodul minim care nu e in MST deja
	for (int i = 0; i < nrNoduri - 1; i++) {
		int minKey = findMinimumCost(key, set, nrNoduri);
		set[minKey] = 1;
		for (int j = 0; j < nrNoduri; j++) {
			if (graf[minKey][j] && set[j] == 0 && graf[minKey][j] < key[j]) {
				key[j] = graf[minKey][j];
				parinte[j] = minKey;
			}
		}
	}
	printMinTree(parinte, graf, nrNoduri);
}

int main() {
	int nrNoduri = readFromFile("input.txt");
	printf("Numarul de noduri din graf este: %d\n\n", nrNoduri);
	prim(graf, nrNoduri);
	return 0;
}
