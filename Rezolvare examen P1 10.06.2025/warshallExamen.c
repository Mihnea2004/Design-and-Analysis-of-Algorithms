#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int matrice[SIZE][SIZE];
int W[SIZE][SIZE];
int nrMaxNoduri;
int nrNoduri;

void readFromFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror("Eroare la deschiderea fisierului");
        exit(EXIT_FAILURE);
    }

    if(fscanf(file, "%d", &nrMaxNoduri) != 1){
        perror(NULL);
        exit(-1);
    }

    if(fscanf(file, "%d", &nrNoduri) != 1){
        perror(NULL);
        exit(-1);
    }

    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            if(fscanf(file, "%d", &matrice[i][j]) != 1){
                perror(NULL);
                exit(-1);
            }
        }
    }

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }

    printf("Noduri: %d\n", nrNoduri);
}

void warshall(){
    for(int i = 0; i < nrNoduri; i++)
        for(int j = 0; j < nrNoduri; j++)
            W[i][j] = matrice[i][j];

    for(int k = 0; k < nrNoduri; k++)
        for(int i = 0; i < nrNoduri; i++)
            for(int j = 0; j < nrNoduri; j++)
                if(W[i][j] == 0)
                    W[i][j] = W[i][k] && W[k][j];
}

void printMatrix(int matrice[SIZE][SIZE]){
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}

int permisiuni(int angajat){ //permisiunile unui angajat (de pe o linie)
    int permisiuni = 0;
    for(int i = 0; i < nrNoduri; i++)
        if(W[angajat][i] == 1)
            permisiuni++;

    return permisiuni;
}

void celeMaiMultePermisiuni(){
    int maxim = 0;
    for(int i = 0; i < nrNoduri; i++){
        int p = permisiuni(i);
        if(p > maxim)
            maxim = p;
    }

    for(int i = 0; i < nrNoduri; i++)
        if(permisiuni(i) == maxim)
            printf("%d ", i);

    printf("\n");
}

void permisiuniCuRisc(){
    for(int i = 0; i < nrNoduri; i++)
        if(permisiuni(i) >= nrMaxNoduri)
            printf("%d ", i);

    printf("\n");
}

int main(){
    readFromFile("permisiuni.txt");
    printf("\nMatricea initiala: \n");
    printMatrix(matrice);

    warshall();
    printf("\nMatricea dependentelor tranzitive: \n");
    printMatrix(W);

    printf("\nAngajatii cu cele mai multe permisiuni: ");
    celeMaiMultePermisiuni();

    printf("\nPermisiunile cu risc de securitate: ");
    permisiuniCuRisc();
    return 0;
}