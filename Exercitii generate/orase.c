#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
int matrice[SIZE][SIZE];
int nrNoduri;
int vizitat[SIZE];

void readFromFile(char *fileName){
    FILE* file = fopen(fileName, "r");
	if(file == NULL){
		perror("Error opening file!");
		exit(-1);
	}

    if(fscanf(file, "%d", &nrNoduri) != 1){
        perror(NULL);
        exit(-1);
    }

    char x, y;
    int cost;
    while(fscanf(file, " %c %c %d", &x, &y, &cost) == 3){
        int i = x - 'A';
        int j = y - 'A';
        matrice[i][j] = cost;
    }

    if(fclose(file) != 0){
		perror("Error closing file!");
		exit(-1);
	}
}

void printMatrix(){
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++)
            printf("%d ", matrice[i][j]);
        printf("\n");
    }
}

int gradIntern(int nod){
    int sum = 0;
    for(int i = 0; i < nrNoduri; i++)
        if(matrice[i][nod])
            sum += matrice[i][nod];

    return sum;
}

int gradExtern(int nod){
    int sum = 0;
    for(int i = 0; i < nrNoduri; i++)
        if(matrice[nod][i])
            sum += matrice[nod][i];

    return sum;
}

void calculeazaDiferenta(int v[]){
    for(int i = 0; i < nrNoduri; i++)
        v[i] = gradExtern(i) - gradIntern(i);
}

void printArray(int v[]){
    for(int i = 0; i < nrNoduri; i++)
        printf("%d ", v[i]);
}

int gasestePlecarileMaxime(int v[]){
    int maxim = v[0];
    int poz = 0;
    for(int i = 0; i < nrNoduri; i++){
        if(v[i] > maxim){
            maxim = v[i];
            poz = i;
        }
    }

    return poz;
}

int dfs(int nodStart){
    vizitat[nodStart] = 1;
    int maxim = 0;

    for(int i = 0; i < nrNoduri; i++){
        if(matrice[nodStart][i] != 0 && vizitat[i] == 0){
            int len = dfs(i);
            if(len > maxim)
                maxim = len;
        }
    }
    vizitat[nodStart] = 0;

    return 1 + maxim;
}

int main(){
    readFromFile("orase.txt");
    printMatrix();

    int diferenta[SIZE];
    calculeazaDiferenta(diferenta);
    printf("Vectorul diferentelor: ");
    printArray(diferenta);

    int oras = gasestePlecarileMaxime(diferenta);
    printf("\nOrasul cu cele mai multe plecari in plus fata de veniri este: %c\n", 'A' + oras);
    
    int maxim = 0;
    for(int i = 0; i < nrNoduri; i++){
        int len = dfs(i);
        if(len > maxim)
            maxim = len;
    }

    printf("Cel mai lung drum format din orase diferite are lungimea: %d\n", maxim);
}