#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE 100
int matrice[SIZE][SIZE];
int S[SIZE];
int nrNoduri = 0;

void readFromFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        perror("Error opening file!\n");
        exit(-1);
    }

    if(fscanf(file, "%d", &nrNoduri) != 1){
        perror("Error reading from file!\n");
        exit(-1);
    }

    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            if(fscanf(file, "%d", &matrice[i][j]) != 1){
                perror("Error reading from file!\n");
                exit(-1);
            }
        }
    }

    if(fclose(file) != 0){
        perror("Error closing file!\n");
        exit(-1);
    }
    // printf("Noduri: %d\n", nrNoduri);
}

void printMatrix(){
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}

void unite(int x, int y){
    int from = S[y];
    int to = S[x];

    for(int i = 0; i < nrNoduri; i++)
        if(S[i] == from)
            S[i] = to;
}

void init(){
    for(int i = 0; i < nrNoduri; i++)
        S[i] = i;
}

void alegeMuchiaMinima(int *u, int *v){
    int minim = INT_MAX;
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
    init();

    int pas = 0;
    int costMinim = 0;
    int u = -1, v = -1;

    while(pas < nrNoduri - 1){
        alegeMuchiaMinima(&u, &v);

        //printf("Muchia: %d - %d, Cost: %d\n", u, v, matrice[u][v]);
        unite(u, v);
        costMinim += matrice[u][v];
        pas++;
    }

    printf("%d\n", costMinim);
}

int main(){
    readFromFile("ex2.txt");
    // printMatrix();
    kruskal();
    return 0;
}
