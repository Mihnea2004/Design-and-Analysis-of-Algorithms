/*
Departamentul de urbanism al unui oraș trebuie să conecteze toate cartierele la utilitățile esențiale (apă, electricitate, gaz) la un cost minim. 
Aceștia dispun de estimări de cost pentru instalarea rețelelor între diferite zone, care includ:
    Costuri de instalare ce variază în funcție de teren și distanță
    Cerința ca toate cartierele să fie conectate (direct sau indirect)
    Constrângeri bugetare care impun găsirea unei soluții cât mai economice
    Necesitatea de a evita conexiunile redundante care nu reduc costul total
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 50
int matrice[SIZE][SIZE];
int S[SIZE];
int nrNoduri;

void readFromFile(char *fileName){
    FILE* file = fopen(fileName, "r");
	if(file == NULL){
		perror("Error opening file!");
		exit(-1);
	}

    if(fscanf(file, "%d", &nrNoduri) != 1){
        perror("Error reading from file!");
		exit(-1);
    }

    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            if(fscanf(file, "%d", &matrice[i][j]) != 1){
                perror("Error reading from file!");
		        exit(-1);
            }
        }
    }

    if(fclose(file) != 0){
		perror("Error closing file!");
		exit(-1);
	}
}

void printMatrix(){
    printf("Matricea de costuri: \n");
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            printf("%5d ", matrice[i][j]);
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
            if(S[i] != S[j] && matrice[i][j] < minim){
                minim = matrice[i][j];
                *u = i;
                *v = j;
            }
        }
    }
}

void afiseazaMuchiaMinima(){
    int minim = INT_MAX;
    int u = -1;
    int v = -1;

    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            if(S[i] != S[j] && matrice[i][j] < minim){
                minim = matrice[i][j];
                u = i;
                v = j;
            }
        }
    }

    if(u != -1)
        printf("Muchia cu costul minim: %d - %d, Cost: %d\n", u, v, matrice[u][v]);
}

void kruskal(){
    init();
    int pas = 0;
    int costTotal = 0;

    while(pas < nrNoduri - 1){
        int u, v;
        alegeMuchiaMinima(&u, &v);

        if(u == -1)
            break;
        
        printf("Muchia %d - %d, Cost: %d\n", u, v, matrice[u][v]);
        pas++;
        unite(u, v);
        costTotal += matrice[u][v];
    }

    if(pas == nrNoduri - 1)
        printf("Graful este conex!\n");
    else
        printf("Graful are mai multe componente conexe!\n");

    printf("Cost total: %d\n", costTotal);
}

int main(){
    readFromFile("ex5.txt");
    printMatrix();

    afiseazaMuchiaMinima();
    kruskal();

    return 0;
}