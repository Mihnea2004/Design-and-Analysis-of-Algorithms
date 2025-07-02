/*
Problemă 2 – Arbore genealogic N-ar
Un trib antic își păstrează evidența familiei sub forma unui arbore genealogic general (fiecare persoană poate avea oricâți copii).

Arborele este construit dintr-un fișier care conține:

N linii de forma: părinte copil

Cerințe:
    Afișează pentru fiecare persoană numărul de descendenți (copii, nepoți etc.)
    Afișează nivelul de adâncime maxim al arborelui (adică generația cea mai îndepărtată)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

char tata[SIZE][SIZE];
char copil[SIZE][SIZE];
char persoane[SIZE][SIZE];
int nrPersoane;
int nrRelatii;
int matrice[SIZE][SIZE];

void readFromFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror("Eroare la deschiderea fisierului");
        exit(EXIT_FAILURE);
    }

    while(fscanf(file, "%s %s", tata[nrRelatii], copil[nrRelatii]) == 2){
        nrRelatii++;
    }

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }

    printf("\nNumar relatii: %d\n", nrRelatii);
}

int adaugaPersoana(char *nume){
    for(int i = 0; i < nrPersoane; i++)
        if(strcmp(persoane[i], nume) == 0)
            return i; // deja exista

    strcpy(persoane[nrPersoane], nume);
    return nrPersoane++;
}

int cautaPersoana(char *nume){
    for(int i = 0; i < nrPersoane; i++)
        if(strcmp(persoane[i], nume) == 0)
            return i;
    return -1;
}

void construiesteArbore(){
    for(int i = 0; i < nrRelatii; i++){
        int t = adaugaPersoana(tata[i]);
        int c = adaugaPersoana(copil[i]);
        matrice[t][c] = 1;
    }
}

int esteCopil(char *nume){
    int c = cautaPersoana(nume); // nu modifică vectorul de persoane
    if (c == -1) return 0;

    for(int i = 0; i < nrPersoane; i++)
        if(matrice[i][c] == 1)
            return 1;

    return 0;
}

int numarDescendenti(int nod){
    int count = 0;
    for(int i = 0; i < nrPersoane; i++)
        if(matrice[nod][i] == 1)
            count += 1 + numarDescendenti(i);

    return count;
}

int adancimeMaxima(int nod){
    int maxim = 0;
    for(int i = 0; i < nrPersoane; i++){
        if(matrice[nod][i] == 1){
            int h = adancimeMaxima(i);
            if(h > maxim)
                maxim = h;
        }
    }

    return maxim + 1;
}

int main(){
    readFromFile("familie.txt");
    construiesteArbore();

    int radacina = -1;
    for(int i = 0; i < nrPersoane; i++){
        if(!esteCopil(persoane[i])){
            radacina = i;
            break;
        }
    }

    if(radacina == -1){
        printf("Nu exista radacina!\n");
        return 1;
    }

    printf("\nRadacina este: %s\n", persoane[radacina]);
    printf("\nAdancimea maxima este: %d\n", adancimeMaxima(radacina));

    printf("\nDescendenti:\n");
    for(int i = 0; i < nrPersoane; i++){
        int d = numarDescendenti(i);
        printf("Persoana: %s -> %d\n", persoane[i], d);
    }

    return 0;
}