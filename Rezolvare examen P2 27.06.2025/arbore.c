#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

typedef struct{
    int cheie;
    int primFiu;
    int frateDreapta;
} Nod;

typedef struct{
    Nod nodes[SIZE + 1];
    int size;
} Tree;

Tree init(Tree a){
    for(int i = 0; i < SIZE; i++){
        a.nodes[i].cheie = 0;
        a.nodes[i].primFiu = 0;
        a.nodes[i].frateDreapta = 0;
    }
    a.size = 0;

    return a;
}

Tree inserare(Tree a, int parinte, int cheie){
    a.size++;
    a.nodes[a.size].cheie = cheie;
    if(parinte == 0){
        a.nodes[a.size].frateDreapta = 0;
        return a;
    }

    if(a.nodes[parinte].primFiu == 0){
        a.nodes[parinte].primFiu = a.size;
    }
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
    if(file == NULL){
        perror("Error opening file!\n");
        exit(-1);
    }

    int parinte, cheie;
    while(fscanf(file, "%d,%d", &cheie, &parinte) == 2){
        // printf("%d,%d\n", parinte, cheie);
        *a = inserare(*a, parinte, cheie);
    }

    if(fclose(file) != 0){
        perror("Error closing file!\n");
        exit(-1);
    }
}

void preordine(Tree a, int radacina){
    if(radacina <= 0 || radacina > a.size){
        return;
    }

    printf("%d ", a.nodes[radacina].cheie);

    int copil = a.nodes[radacina].primFiu;
    preordine(a, copil);

    while((copil = a.nodes[copil].frateDreapta) != 0)
        preordine(a, copil);   
}

void cautaNivel(Tree a, int radacina, int nivel, int *search, int id){
    if(radacina <= 0 || radacina > a.size){
        return;
    }

    printf("%d ", a.nodes[radacina].cheie); 

    if(*search != 0 && a.nodes[radacina].cheie == radacina){
        *search = nivel;
        return;
    }

    int copil = a.nodes[radacina].primFiu;
    cautaNivel(a, copil, nivel + 1, search, id);

    while((copil = a.nodes[copil].frateDreapta) != 0)
        cautaNivel(a, copil, nivel + 1, search, id);
}

// void display(Tree a){
//     printf("Index:   ");
//     for(int i = 0; i <= a.size; i++)
//         printf("%d ", i);
//     printf("\n");

//     printf("Cheie:   ");
//     for(int i = 0; i <= a.size; i++)
//         printf("%d ", a.nodes[i].cheie);
//     printf("\n");

//     printf("PrimFiu: ");
//     for(int i = 0; i <= a.size; i++)
//         printf("%d ", a.nodes[i].primFiu);
//     printf("\n");

//     printf("FrateDr: ");
//     for(int i = 0; i <= a.size; i++)
//         printf("%d ", a.nodes[i].frateDreapta);
//     printf("\n");
// }

int main(){
    Tree a = init(a);
    readFromFile("ex1.txt", &a);
    //display(a);

    printf("\nPreordine: ");
    preordine(a, 1);

//     int 
//     cautaNivel(a, 1, 1, )
}