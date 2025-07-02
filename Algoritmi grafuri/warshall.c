#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 20

int matrice[SIZE][SIZE];
int nrNoduri;
int W[SIZE][SIZE];

int readFromFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
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

    return nrNoduri;
}

void displayArray(int matrice[SIZE][SIZE]){
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++)
            printf("%d ", matrice[i][j]);
        printf("\n");
    }
    printf("\n");
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

void accesari(){
    int maxim = INT_MIN;
    int nodMax = -1;

    for(int i = 0; i < nrNoduri; i++){
        int counter = 0;
        for(int j = 0; j < nrNoduri; j++)
            if(W[i][j] == 1)
                counter++;

        if(counter > maxim){
            maxim = counter;
            nodMax = i;
        }
    }

    printf("Cele mai multe accesari le are nodul %d, avand %d accesari!\n", nodMax, maxim);
}

void depasesteAccesari(int maxAccesari){
    int counter = 0;
    for(int i = 0; i < nrNoduri; i++){
        counter = 0;
        for(int j = 0; j < nrNoduri; j++)
            if(W[i][j] == 1)
                counter++;

        if(counter > maxAccesari)
            printf("%d ", i);
    }
}

int esteConex(){
    for(int i = 0; i < nrNoduri; i++)
        for(int j = 0; j < nrNoduri; j++)
            if(W[i][j] == 0 && i != j)
                return 0;
       
    return 1;
}

// int esteTareConex(){
//     for(int i = 0; i < nrNoduri; i++)
//         for(int j = 0; j < nrNoduri; j++)
//             if((W[i][j] == 0 || W[j][i] == 0) && i != j)
//                 return 0;
       
//     return 1;
// }

int main(){
    nrNoduri = readFromFile("warshall.txt");
    printf("In graf sunt %d noduri!\n", nrNoduri);

    displayArray(matrice);

    printf("Matricea dependentelor tranzitive: \n");
    warshall();
    displayArray(W);

    accesari();
    printf("\n");

    printf("Nodurile care depasesc numarul maxim de accesari sunt: ");
    depasesteAccesari(2);
    printf("\n\n");

    if(esteConex())
        printf("Graful este conex!\n");
    else
        printf("Graful nu este conex!\n");

    printf("\n");
    return 0;
}