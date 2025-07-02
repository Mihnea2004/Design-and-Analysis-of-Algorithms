#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int matrice[SIZE][SIZE];
int S[SIZE];
int nrNoduri;

void readFromFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        perror("pacient.txt open failed");
        exit(-1);
    }

    char x, y;
    int cost;

    while(fscanf(file, " %c %c %d", &x, &y, &cost) == 3){
        int i = x - 'A';
        int j = y - 'A';

        matrice[i][j] = cost;
        matrice[j][i] = cost;

        if(i + 1 > nrNoduri)
            nrNoduri = i + 1;
        if(j + 1 > nrNoduri)
            nrNoduri = j + 1;
    }

    if(fclose(file) != 0){
        perror("pacient.txt close failed");
        exit(-1);
    }

    printf("Noduri: %d\n", nrNoduri);
}

void printArray(){
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++)
            printf("%2d ", matrice[i][j]);
        printf("\n");
    }

    printf("\n");
}

void unite(int x, int y){
    int from = S[y];
    int to = S[x];

    for(int i = 0; i < nrNoduri; i++)
        if(S[i] == from)
            S[i] = to;
}

void alegeMuchiaMinima(int *u, int *v){
    int minim = 9999;
    *u = -1, *v = -1;

    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            if(matrice[i][j] != 0 && S[i] != S[j] && matrice[i][j] < minim){
                minim = matrice[i][j];
                *u = i;
                *v = j;
            }
        }
    }
}

void kruskal(){
    int costTotal = 0;
    int pas = 0;

    for(int i = 0; i < nrNoduri; i++)
        S[i] = i;

    while(pas < nrNoduri - 1){
        int u, v;
        alegeMuchiaMinima(&u, &v);

        if(u == -1)
            break;

        printf("Muchia: %c - %c, Cost: %d\n", u + 'A', v + 'A', matrice[u][v]);
        pas++;
        costTotal += matrice[u][v];
        unite(u, v);
    }

    printf("\nCost total: %d\n", costTotal);
}

int main(){
    readFromFile("kruskal.txt");
    printArray();
    kruskal();
    return 0;
}