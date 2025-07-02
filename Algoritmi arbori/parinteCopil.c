#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct{
    char cheie[SIZE];
    int parinte;
}Nod;

typedef struct{
    Nod nodes[SIZE];
    int size;
}Tree;

Tree init(Tree a){
    for(int i = 0; i < SIZE; i++){
        strcpy(a.nodes[i].cheie, "");
        a.nodes[i].parinte = 0;
    }
    a.size = 0;

    return a;
}

Tree insertNode(Tree a, int parinte, char *cheie){
    a.size++;
    strcpy(a.nodes[a.size].cheie, cheie);
    a.nodes[a.size].parinte = parinte;

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
    printf("Size:     ");
    for(int i = 0; i <= a.size; i++)
        printf("%2d ", i);
    printf("\n");

    printf("Chei:     ");
    for(int i = 0; i <= a.size; i++)
        printf("%2s ", a.nodes[i].cheie);
    printf("\n");

    printf("Parinte:  ");
    for(int i = 0; i <= a.size; i++)
        printf("%2d ", a.nodes[i].parinte);
    printf("\n");
}

int primFiu(Tree a, int radacina){
    if(radacina <= 0 || radacina > a.size)
        return 0;

    for(int i = 1; i <= a.size; i++)
        if(a.nodes[radacina].parinte == radacina)
            return i;

    return 0;
}

int frateDreapta(Tree a, int radacina){
    if(radacina <= 0 || radacina > a.size)
        return 0;

    for(int i = radacina + 1; i <= a.size; i++)
        if(a.nodes[i].parinte == a.nodes[radacina].parinte)
            return i;

    return 0;
}

void preordine(Tree a, int radacina, int nivel){
    if(radacina <= 0 || radacina > a.size)
        return;

    printf("%s ", a.nodes[radacina].cheie);

    for(int i = 1; i <= a.size; i++)
        if(a.nodes[i].parinte == radacina)
            preordine(a, i, nivel + 1);
}

void inordine(Tree a, int radacina, int nivel){
    if(radacina <= 0 || radacina > a.size)
        return;

    int copil = primFiu(a, radacina);
    inordine(a, copil, nivel + 1);

    printf("%s ", a.nodes[radacina].cheie);

    while((copil = frateDreapta(a, copil)) != 0)
        inordine(a, copil, nivel + 1);
}

int gradMaxim(Tree a){
    int maxim = 0;
    
    int freq[SIZE] = {0};

    for(int i = 1; i <= a.size; i++)
        if(a.nodes[i].parinte != 0)
            freq[a.nodes[i].parinte]++;

    for(int i = 1; i <= a.size; i++)
        if(freq[i] > maxim)
            maxim = freq[i];
            
    return maxim;
}

int inaltimeMaxima(Tree a, int radacina){
    if(radacina == 0)
        return 0;

    int maxim = 0;

    for(int i = 1; i <= a.size; i++){
        if(a.nodes[i].parinte == radacina){
            int h = inaltimeMaxima(a, i);
            if(h > maxim)
                maxim = h;
        }
    }

    return maxim + 1;
}

int main(){
    Tree a = init(a);
    readFromFile("primFiu.txt", &a);
    afisare(a);
    printf("\nPreordine: ");
    preordine(a, 1, 1);
    printf("\nGrad maxim: %d\n", gradMaxim(a));
    printf("\nInaltime maxima: %d\n", inaltimeMaxima(a, 1) - 1);
}