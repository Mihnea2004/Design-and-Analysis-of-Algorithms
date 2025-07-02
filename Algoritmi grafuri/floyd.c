#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100
#define INF INT_MAX

int D[SIZE][SIZE];
int T[SIZE][SIZE];
int nrNoduri;

void readFromFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror(NULL);
        exit(-1);
    }

    fscanf(file, "%d", &nrNoduri);

    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            int val;
            fscanf(file, "%d", &val);
            if(val == 0 && i != j)
                D[i][j] = INF;
            else
                D[i][j] = val;

            T[i][j] = -1;
        }
    }

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }

    printf("Noduri: %d\n", nrNoduri);
}

void printArray(){
    printf("\n");
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            if(D[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", D[i][j]);
        }
        printf("\n");
    }
}

void floyd(){
    for(int k = 0; k < nrNoduri; k++){
        for(int i = 0; i < nrNoduri; i++){
            for(int j = 0; j < nrNoduri; j++){
                if(D[i][k] != INF && D[k][j] != INF && D[i][k] + D[k][j] < D[i][j]){
                    D[i][j] = D[i][k] + D[k][j];
                    T[i][j] = k;
                }
            }
        }
    }
    printf("\n");
}

void traseu(int i, int j){
    int k = T[i][j];
    if(k == -1)
        return;

    traseu(i, k);
    printf("%d ", k);
    traseu(k, j);
}

void drum(int start, int destination){
    printf("%d -> %d: ", start, destination);

    printf("%d ", start);

    traseu(start, destination);

    printf("%d ", destination);

    printf("Distanta: %d\n", D[start][destination]);
}

void afiseazaToateDrumurile(){
    for(int i = 0; i < nrNoduri; i++)
        for(int j = 0; j < nrNoduri; j++)
            if(i != j)
                drum(i, j);
}

int main(){
    readFromFile("floyd.txt");
    printArray();
    floyd();
    printArray();
    //drum(0, 2);
    afiseazaToateDrumurile();
    return 0;
}