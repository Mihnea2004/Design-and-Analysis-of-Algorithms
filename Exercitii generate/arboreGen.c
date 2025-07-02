/*
„Evaluarea structurii ierarhice a unui organism biologic”
Un laborator de cercetare modelează structura ierarhică a unui organism viu (precum un arbore filogenetic sau un sistem de organe)
sub forma unui arbore generalizat, unde fiecare entitate (organism, subsistem, element) poate avea oricâți „descendenți”.

Cerinte:
    Construiește arborele în reprezentarea prim fiu – frate dreapta.
    Afișează numele tuturor nodurilor de pe fiecare nivel (traversare pe nivel – BFS).
    Calculează adâncimea maximă a structurii.
    Afișează toți descendenții ai unui nod dat (ex: „Ce conține sistemul digestiv?”).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct{
    char cheie[SIZE];
    int primFiu;
    int frateDreapta;
} Nod;

typedef struct{
    Nod nodes[SIZE];
    int size;
} Tree;

Tree init(Tree a){
    for(int i = 0; i < SIZE; i++){
        strcpy(a.nodes[i].cheie, "");
        a.nodes[i].primFiu = 0;
        a.nodes[i].frateDreapta = 0;
    }
    a.size = 0;

    return a;
}

Tree insertNode(Tree a, int parinte, char *copil){
    a.size++;
    strcpy(a.nodes[a.size].cheie, copil);
    if(parinte == 0){
        a.nodes[a.size].frateDreapta = 0;
        return a;
    }

    if(a.nodes[parinte].primFiu == 0)
        a.nodes[parinte].primFiu = a.size;

    else{
        int frate = a.nodes[parinte].primFiu;
        while(a.nodes[frate].frateDreapta != 0){
            frate = a.nodes[frate].frateDreapta;
        }
        a.nodes[frate].frateDreapta = a.size;
    }

    return a;
}

void readFromFile(char *fileName, Tree *a){
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror("Eroare la deschiderea fisierului");
        exit(EXIT_FAILURE);
    }

    int radacina;
    char cheie[SIZE];

    while(fscanf(file, "%d %s", &radacina, cheie) == 2){
        *a = insertNode(*a, radacina, cheie);
    }

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }
}

void display(Tree a){
    printf("Index: ");
    for(int i = 0; i <= a.size; i++)
        printf("%d ", i);
    printf("\n");

    printf("Cheie:  ");
    for(int i = 0; i <= a.size; i++)
        printf("%s ", a.nodes[i].cheie);
    printf("\n");

    printf("PrimF: ");
    for(int i = 0; i <= a.size; i++)
        printf("%d ", a.nodes[i].primFiu);
    printf("\n");

    printf("Frate: ");
    for(int i = 0; i <= a.size; i++)
        printf("%d ", a.nodes[i].frateDreapta);
    printf("\n");
}

void preordine(Tree a, int radacina, int nivel){
    if(radacina <= 0 || radacina > a.size)
        return;

    printf("%s ", a.nodes[radacina].cheie);

    int copil = a.nodes[radacina].primFiu;
    preordine(a, copil, nivel + 1);

    while((copil = a.nodes[copil].frateDreapta) != 0)
        preordine(a, copil, nivel + 1);
}

int adancimeMaxima(Tree a, int radacina){
    if(radacina <= 0 || radacina > a.size)
        return 0;

    int maxim = 0;
    int copil = a.nodes[radacina].primFiu;
    while(copil != 0){
        int h = adancimeMaxima(a, copil);
        if(h > maxim)
            maxim = h;

        copil = a.nodes[copil].frateDreapta;
    }

    return maxim + 1;
}

void descendenti(Tree a, int radacina){
    if(radacina <= 0 || radacina > a.size)
        return;

    int copil = a.nodes[radacina].primFiu;
    while(copil != 0){
        printf("%s ", a.nodes[copil].cheie);
        descendenti(a, copil);
        copil = a.nodes[copil].frateDreapta;
    }
}

int main(){
    Tree a = init(a);
    readFromFile("arboreGen.txt", &a);

    display(a);

    printf("\nPreordine: \n");
    preordine(a, 1, 1);

    printf("\nAdancimea maxima: %d\n", adancimeMaxima(a, 1) - 1);

    printf("\nDescendenti: \n");
    descendenti(a, 1);
}