/*
O companie de producție urmărește relațiile cu furnizorii pentru a evalua riscurile din lanțul de aprovizionare. Aceasta are nevoie să înțeleagă:
    Ce furnizori pot influența în cele din urmă fiecare produs (atât dependențe directe, cât și indirecte)
    Cum o întrerupere la un furnizor poate genera un efect de domino în lanțul de aprovizionare
    Care relații cu furnizorii generează cele mai mari vulnerabilități
    Matricea completă a dependențelor, pentru planificarea riscurilor

Fiind date informațiile despre relațiile dintre furnizori, proiectează un algoritm care să calculeze toate dependențele posibile 
din lanțul de aprovizionare și să analizeze riscurile sistemice.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

int matrice[SIZE][SIZE];
int W[SIZE][SIZE];
int nrNoduri;

void initMatrix(){
    for(int i = 0; i < nrNoduri; i++)
        for(int j = 0; j < nrNoduri; j++)
            matrice[i][j] = 0;
}

void displayMatrix(int matrice[SIZE][SIZE]){
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++)
            printf("%d ", matrice[i][j]);
        printf("\n");
    }
    printf("\n");
}

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

    initMatrix();
    int x, y;
    while(fscanf(file, "%d %d", &x, &y) == 2)
        matrice[x][y] = 1;

    if(fclose(file) != 0){
		perror("Error closing file!");
		exit(-1);
	}
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

void esteAfectat(){
    int maxim = 0;
    int maxPoz = -1;

    for(int i = 0; i < nrNoduri; i++){
        printf("Furnizorul %c este afectat de: ", 'A' + i);
        int count = 0;
        for(int j = 0; j < nrNoduri; j++){
            if(W[i][j] == 1){
                printf("%c ", 'A' + j);
                count++;
            }
        }

            if(count > maxim){
                maxim = count;
                maxPoz = i;
            }

        printf("\n");
    }

    printf("\nFurnizorul %c este cel mai afectat, avand %d accesari!\n", 'A' + maxPoz , maxim);
}

void vulnerabil(){
    printf("\n");
    int dependente = 0;
    for(int i = 0; i < nrNoduri; i++){
        dependente = 0;
        for(int j = 0; j < nrNoduri; j++){
            if(W[j][i] == 1)
                dependente++;
        }
        printf("Nodul %c are %d dependente!\n", 'A' + i, dependente);
    }
}

void simuleazaCaderea(){
    printf("\n");
    for(int i = 0; i < nrNoduri; i++){
        printf("Nodul %c afecteaza pe: ", 'A' + i);
        int count = 0;
        for(int j = 0; j < nrNoduri; j++){
            if(W[j][i] == 1){
                printf("%c ", 'A' + j);
                count++;
            }
        }
        if(count == 0)
            printf("nimeni.");

        printf("\n");
    }
}

int main(){
    readFromFile("ex6.txt");
    printf("Matricea initiala: \n");
    displayMatrix(matrice);

    warshall();
    printf("Matricea dependentelor tranzitive: \n");
    displayMatrix(W);

    esteAfectat();

    simuleazaCaderea();

    vulnerabil();

    return 0;
}