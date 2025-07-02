#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

#define SIZE 20
int matrice[SIZE][SIZE];

void initialiseArray(){
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            matrice[i][j] = 0;
}

void printArray(int size){ //pt matricea de adiacenta
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            printf("%d ", matrice[i][j]);
        printf("\n");
    }
}

int readMatrix(FILE *file){
    int nrNoduri;
    int x;
    int a[100][100];
    fscanf(file, "%d", &nrNoduri);
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            fscanf(file, "%d", &x);
            a[i][j] = x;
        }
    }

    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    return nrNoduri;
}

int readFromFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        perror("An error occured while trying to open the file!\n");
        exit(-1);
    }

    int nrNoduri = 0;
    if(fscanf(file, "%d", &nrNoduri) != 1){
        perror("nu merge boss");
        exit(-1);
    }

    int x, y;
    while(fscanf(file, "%d %d", &x, &y) == 2){
        matrice[x%nrNoduri][y%nrNoduri] = 1;
        matrice[y%nrNoduri][x%nrNoduri] = 1;
    }

    // for(int i = 0; i < nrMuchii; i++){
    //     int x, y;
    //     if(fscanf(file, "%d %d", &x, &y) != 2){
    //         perror(NULL);
    //         exit(-1);
    //     }

    //     matrice[x][y] = matrice[y][x] = 1;
    // }

    if(fclose(file) != 0){
        perror("An error occured while trying to close the file!\n");
        exit(-1);
    }

    return nrNoduri;
}

void BFS(int matrice[SIZE][SIZE], int start){
    int vizitat[SIZE] = {0};
    int coada[SIZE];
    int prim = 0, ultim = 0;

    vizitat[start] = 1;
    coada[ultim++] = start;

    while(prim < ultim){
        int current = coada[prim++];
        printf("%d ", current);

        for(int i = 0; i < SIZE; i++){
            if(matrice[current][i] == 1 && vizitat[i] == 0){
                vizitat[i] = 1;
                coada[ultim++] = i;
            }
        }
    }
    printf("\n");
}

void DFSRecursive(int matrice[SIZE][SIZE], int *vizitat, int start){
    vizitat[start] = 1;
    printf("%d ", start);

    for(int i = 0; i < SIZE; i++)
        if(matrice[start][i] == 1 && vizitat[i] == 0)
            DFSRecursive(matrice, vizitat, i);
}

void DFS(int matrice[SIZE][SIZE], int start){
    int vizitat[SIZE] = {0};
    DFSRecursive(matrice, vizitat, start);
    printf("\n");
}

int findGradNod(int matrice[SIZE][SIZE], int nod){
    int grad = 0;

    for(int i = 0; i < SIZE; i++)
        grad += matrice[nod][i];

    return grad;
}

int findGradMaximGraf(int matrice[SIZE][SIZE]){
    int gradMaxim = 0;
    for(int i = 0; i < SIZE; i++)
        if(findGradNod(matrice, i) > gradMaxim)
            gradMaxim = findGradNod(matrice, i);

    return gradMaxim;
}

void shortestPath(int matrice[SIZE][SIZE], int start, int end){
    int vizitat[SIZE] = {0};
    int parinte[SIZE] = {0};
    int coada[SIZE], prim = 0, ultim = 0;
    int index = 0;

    vizitat[start] = 1;
    parinte[start] = -1;
    coada[ultim++] = start;

    while(prim < ultim){
        int current = coada[prim++];

        for(int i = 0; i < SIZE; i++){
            if(matrice[current][i] == 1 && vizitat[i] == 0){
                vizitat[i] = 1;
                parinte[i] = current;
                index = i + 1;
                coada[ultim++] = i;
            }
        }
    }

    int drum[SIZE] = {0};
    int i = end;
    
    index = 0;
    drum[index++] = i;

    while(i != start){
        i = parinte[i];
        drum[index++] = i;
    }

    for(int j = index - 1; j >= 0; j--)
        printf("%d ", drum[j]);

    printf("\n");
}

int countComponenteConexe(int matrice[SIZE][SIZE], int nrNoduri){
	int count = 0;
	int vizitat[SIZE] = { 0 };
	printf("Parcurgere totala in adancime: ");
	for(int i = 0; i < nrNoduri; i++){
		if(vizitat[i] == 0){
			count++;
			DFSRecursive(matrice, vizitat, i);
		}
	}
	return count;
}

int main(int argc, char **argv){
    initialiseArray();

    int nrNoduri = readMatrix(argv[1]);  

    //int nrNoduri = readFromFile(argv[1]);

    printf("Matrice de adiacenta: \n");
    printArray(12);

    printf("BFS: ");
    BFS(matrice, 0);

    printf("DFS: ");
    DFS(matrice, 0);

    printf("Shortest path: ");
    shortestPath(matrice, 0, 12);

    int counter = countComponenteConexe(matrice, nrNoduri);
    printf("\n\nNumarul componentelor conexe din graf este: %d\n", counter);

    int gradMaxim = findGradMaximGraf(matrice);
    printf("\n\nGradul maxim al grafului este: %d\n", gradMaxim);

    return 0;
}