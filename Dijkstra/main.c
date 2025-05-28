#define _CRT_SECURE_NO_WARNINGS
#define SIZE 20

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int matrice[SIZE][SIZE];
int distanta[SIZE]; //D
int vizitat[SIZE];
int parinte[SIZE]; //T

void initiateArray(int matrice[SIZE][SIZE], int nrNoduri) {
	for (int i = 0; i < nrNoduri; i++)
		for (int j = 0; j < nrNoduri; j++)
			if (matrice[i][j] == 0 && i != j)
				matrice[i][j] = INT_MAX;
}

int readFromFile(char* fileName){
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		perror(NULL); 
		exit(-1);
	}

	int nrNoduri;
	if (fscanf(file, "%d", &nrNoduri) != 1)
	{
		perror("Error reading n!");
		exit(-1);
	}

	int a, b, c;
	while (fscanf(file, "%d %d %d", &a, &b, &c) == 3)
	{
		matrice[a % nrNoduri][b % nrNoduri] = c;  //pentru orientat
		//matrice[b % n][a % n] = c;  //pentru neorientat
	}

	if (fclose(file) != 0)
	{
		perror(NULL);
		exit(-1);
	}

	initiateArray(matrice, nrNoduri);

	return nrNoduri;
}

void print(int matrice[SIZE][SIZE], int distanta[SIZE], int parinte[SIZE], int nrNoduri) {
	//lista nodurilor
	for (int i = 0; i < nrNoduri; i++)
		printf("%4c ", 'A' + i);
	printf("\n");

	//vectorul distanta
	for (int i = 0; i < nrNoduri; i++)
		printf("%4d ", distanta[i]);
	printf("\n");

	//vectorul parinte
	for (int i = 0; i < nrNoduri; i++)
		printf("%4c ", 'A' + parinte[i]);
	printf("\n\n");
}

// initial, distantele sunt costurile directe de la sursa

void dijkstra(int matrice[SIZE][SIZE], int nrNoduri, int sourceNode) {
	for (int i = 0; i < nrNoduri; i++) {
		vizitat[i] = 0;
		distanta[i] = matrice[sourceNode][i];
		parinte[i] = sourceNode;
	}
	vizitat[sourceNode] = 1;
	distanta[sourceNode] = 0;

	for (int step = 0; step < nrNoduri - 1; step++) {
		int pmin = -1;
		for (int j = 0; j < nrNoduri; j++)
			if (!vizitat[j] && (pmin == -1 || distanta[j] < distanta[pmin]))
				pmin = j;

		if (pmin == -1) break;
		vizitat[pmin] = 1;

		for (int j = 0; j < nrNoduri; j++)
			if (!vizitat[j] && matrice[pmin][j] != INT_MAX &&
				distanta[pmin] + matrice[pmin][j] < distanta[j]) {
				distanta[j] = distanta[pmin] + matrice[pmin][j];
				parinte[j] = pmin;
			}
	}

	print(matrice, distanta, parinte, nrNoduri);
}


void drum(int src, int dest) {
	int arr[SIZE] = { 0 };
	int index = 0;

	int i = dest;
	while (i != src) {
		arr[index++] = i;
		i = parinte[i];
	}

	printf("Drumul de la %d la %d este: ", src, dest);
	printf("%c ", 'A' + src);

	for (int i = index - 1; i >= 0; i--)
		printf("%c ", 'A' + arr[i]);
}

int main() {
	int nrNoduri = readFromFile("input.txt");
	dijkstra(matrice, nrNoduri, 0);
	drum(0, 2);

	return 0;
}