#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct{
    char cheie[SIZE];
    int primFiu;
    int frateDreapta;
}Nod;

typedef struct{
    Nod nodes[SIZE];
    int size;
}Tree;

Tree init(Tree a){
    for(int i = 0; i < SIZE; i++){
        a.nodes[i].primFiu = 0;
        a.nodes[i].frateDreapta = 0;
    }
    a.size = 0;

    return a;
}

Tree insertNode(Tree a, int parinte, char *cheie){
    a.size++;
    strcpy(a.nodes[a.size].cheie, cheie);

    if(parinte == 0){
        a.nodes[a.size].frateDreapta = 0;
        return a;
    }

    if(a.nodes[parinte].primFiu == 0){
        a.nodes[parinte].primFiu = a.size;
    }
    else{
        int copil = a.nodes[parinte].primFiu;
        while(a.nodes[copil].frateDreapta != 0)
            copil = a.nodes[copil].frateDreapta;
        
        a.nodes[copil].frateDreapta = a.size;
    }

    return a;
}

void readFromFile(char *fileName, Tree *radacina){
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror(NULL);
        exit(-1);
    }

    int parinte;
    char cheie[SIZE];

    while(fscanf(file, "%d %s", &parinte, cheie) == 2){
        //printf("%d - %s\n", parinte, cheie);
        *radacina = insertNode(*radacina, parinte, cheie);
    }

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }
}

void afisare(Tree a){
    printf("Size:  ");
    for(int i = 0; i <= a.size; i++)
        printf("%2d ", i);
    printf("\n");

    printf("Chei:  ");
    for(int i = 0; i <= a.size; i++)
        printf("%2s ", a.nodes[i].cheie);
    printf("\n");

    printf("Prim:  ");
    for(int i = 0; i <= a.size; i++)
        printf("%2d ", a.nodes[i].primFiu);
    printf("\n");

    printf("Frate: ");
    for(int i = 0; i <= a.size; i++)
        printf("%2d ", a.nodes[i].frateDreapta);
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

void inordine(Tree a, int radacina, int nivel){
    if(radacina <= 0 || radacina > a.size)
        return;

    int copil = a.nodes[radacina].primFiu;
    inordine(a, copil, nivel + 1);

    printf("%s ", a.nodes[radacina].cheie);

    while((copil = a.nodes[copil].frateDreapta) != 0)
        inordine(a, copil, nivel + 1);
}

int gradMaxim(Tree a){
    int grad = 0;
    int maxim = 0;
    int radacina = 1;
    int copil = a.nodes[radacina].primFiu;

    while(copil != 0){
        grad++;
        copil = a.nodes[copil].frateDreapta;
    }

    if(grad > maxim)
        maxim = grad;

    for(int i = 2; i <= a.size; i++){
        copil = a.nodes[i].primFiu;
        grad = 0;
        while(copil != 0){
            grad++;
            copil = a.nodes[copil].frateDreapta;
        }
        if(grad + 1> maxim)
            maxim = grad + 1;
    }

    return maxim;
}

int inaltimeMaxima(Tree a, int radacina){
    if(radacina == 0)
        return 0;

    int maxim = 0;
    int copil = a.nodes[radacina].primFiu;

    while(copil != 0){
        int h = inaltimeMaxima(a, copil);
        if(h > maxim)
            maxim = h;
        copil = a.nodes[copil].frateDreapta;
    }

    return maxim + 1;
}

int main(){
    Tree a = init(a);
    readFromFile("primFiu.txt", &a);
    afisare(a);
    printf("\nPreordine: ");
    preordine(a, 1, 1);
    printf("\nInordine: ");
    inordine(a, 1, 1);
    printf("\nGrad maxim: %d\n", gradMaxim(a));
    printf("\nInaltime maxima: %d\n", inaltimeMaxima(a, 1) - 1);
}