#define _CRT_SECURE_NO_WARNINGS
#define SIZE 20	

#include <stdio.h>
#include <stdlib.h>

int edge[SIZE][3];
int parent[SIZE];
int rank[SIZE];

int readFromFile(char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		perror(NULL);
		exit(-1);
	}

	//nod1 nod2 cost
	int nrNoduri = 0; //irelevant aici
	if (fscanf(file, "%d", &nrNoduri) != 1) {
		perror(NULL);
		exit(-1);
	}

	int nrMuchii = 0;
	int a, b, c;
	while (fscanf(file, "%d %d %d", &a, &b, &c) == 3) {
		edge[nrMuchii][0] = a;
		edge[nrMuchii][1] = b;
		edge[nrMuchii++][2] = c;
	}

	if (fclose(file) != 0) {
		perror(NULL);
		exit(-1);
	}

	return nrMuchii;
}

int compare(const int v1[], const int v2[]) {
	return v1[2] - v2[2];
}

int findParent(int parent[], int component) {
	if (parent[component] == component)
		return component;

	return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[]) {
	u = findParent(parent, u);
	v = findParent(parent, v);

	if (rank[u] < rank[v])
		parent[u] = v;
	else if(rank[u] > rank[v])
		parent[v] = u;
	else {
		parent[v] = u;
		rank[u]++;
	}
}

int kruskal(int nrMuchii, int edge[SIZE][3]) {
	qsort(edge, nrMuchii, sizeof(edge[0]), compare);

	for (int i = 0; i < nrMuchii; i++) {
		parent[i] = i;
		rank[i] = 0;
	}

	int minCost = 0;
	for (int i = 0; i < nrMuchii; i++) {
		int v1 = findParent(parent, edge[i][0]);
		int v2 = findParent(parent, edge[i][1]);
		if (v1 != v2) {
			unionSet(v1, v2, parent, rank);
			minCost += edge[i][2];
			printf("Muchia: %d - %d -> Cost: %d\n", edge[i][0], edge[i][1], edge[i][2]);
		}
	}

	return minCost;
}

int main() {
	int nrMuchii = readFromFile("input.txt");
	printf("In graf exista %d muchii!\n\n", nrMuchii);

	int x = kruskal(14, edge);
	printf("\nCostul minim este %d!\n", x);

	return 0;
}