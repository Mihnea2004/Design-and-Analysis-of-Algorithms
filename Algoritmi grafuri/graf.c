#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int matrice[SIZE][SIZE];
int vizitat[SIZE];
int nrNoduri;

void readFromFile(char *fileName){
    FILE* file = fopen(fileName, "r");
	if(file == NULL){
		perror("Error opening file!");
		exit(-1);
	}

    fscanf(file, "%d", &nrNoduri);

    int x, y;
    while(fscanf(file, "%d %d", &x, &y) == 2){
        matrice[x][y] = 1;
        matrice[y][x] = 1;
    }

    if(fclose(file) != 0){
		perror("Error closing file!");
		exit(-1);
	}

    printf("Noduri: %d\n", nrNoduri);
}

void printMatrix(){
    printf("Matricea de adiacenta: \n");
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++)
            printf("%d ", matrice[i][j]);
        printf("\n");
    }

    printf("\n");
}

int dfs(int start){
    vizitat[start] = 1;
    int dim = 1;
    
    for(int i = 0; i < nrNoduri; i++){
        if(matrice[start][i] != 0 && vizitat[i] == 0){
            //printf("%d ", i);
            dim += dfs(i);
        }
    }

    return dim;
}

int componenteConexe(){
    int componente = 0;
    int maxim = 0;
    for(int i = 0; i < nrNoduri; i++){
        if(vizitat[i] == 0){
            int dim = dfs(i);
            componente++;
            if(dim > maxim)
                maxim = dim;
        }
    }

    printf("Componenta cea mai mare are %d elemente!\n", maxim);

    return componente;
}

void bfs(int start){
    int vizitat[SIZE] = {0};
    int coada[SIZE], prim = 0, ultim = 0;

    coada[ultim++] = start;
    vizitat[start] = 1;

    while(prim < ultim){
        int current = coada[prim++];
        printf("%d ", current);

        for(int i = 0; i < SIZE; i++){
            if(vizitat[i] == 0 && matrice[current][i] != 0){
                vizitat[i] = 1;
                coada[ultim++] = i;
            }
        }
    }
    printf("\n");
}

void shortestPath(int start, int destination){
    int vizitat[SIZE] = {0};
    int parinte[SIZE] = {0};
    int parinti = 0;
    int coada[SIZE], prim = 0, ultim = 0;

    coada[ultim++] = start;
    vizitat[start] = 1;
    parinte[start] = -1;

    while(prim < ultim){
        int current = coada[prim++];
        printf("%d ", current);

        for(int i = 0; i < SIZE; i++){
            if(vizitat[i] == 0 && matrice[current][i] != 0){
                vizitat[i] = 1;
                parinte[i] = current;
                parinti++;
                coada[ultim++] = i;
            }
        }
    }

    int v[SIZE] = {0};
    int index = 0;
    int i = destination;

    while(i != start){
        v[index++] = i;
        i = parinte[i];
    }

    printf("%d ", start);
    for(int i = index - 1; i >= 0; i--)
        printf("%d ", v[i]);

    printf("\n");
}

int gradMaxim(){
    int grad = 0;
    int maxim = 0;

    for(int i = 0; i < nrNoduri; i++){
        grad = 0;
        for(int j = 0; j < nrNoduri; j++){
            if(matrice[i][j] == 1)
                grad++;

            if(grad + 1 > maxim)
                maxim = grad + 1;
        }
    }

    return maxim;
}

int inaltimeMaxima(int start){
    int viz[SIZE] = {0};
    int nivel[SIZE] = {0};
    int coada[SIZE], prim = 0, ultim = 0;

    coada[ultim++] = start;
    viz[start] = 1;
    nivel[start] = 0;

    int maxNivel = 0;

    while(prim < ultim){
        int current = coada[prim++];

        for(int i = 0; i < nrNoduri; i++){
            if(matrice[current][i] && !viz[i]){
                viz[i] = 1;
                nivel[i] = nivel[current] + 1;
                if(nivel[i] > maxNivel)
                    maxNivel = nivel[i];
                coada[ultim++] = i;
            }
        }
    }

    return maxNivel;
}

int main(){
    readFromFile("graf.txt");
    printMatrix();
    printf("\nComponente conexe: %d\n", componenteConexe());

    printf("\nBFS: ");
    bfs(0);

    printf("\nShortest path: ");
    shortestPath(0, 9);

    printf("\nGrad maxim: %d\n", gradMaxim());
}