#include <stdio.h>
#include <stdlib.h>

typedef struct Nod{
    struct Nod *stanga, *dreapta;
    int cheie;
} Nod;

int nrNoduri;

Nod *creeazaNod(int cheie){
    Nod *nod = malloc(sizeof(Nod));
    if(nod == NULL){
        perror(NULL);
        exit(-1);
    }

    nod -> stanga = NULL;
    nod -> dreapta = NULL;
    nod -> cheie = cheie;

    return nod;
}

Nod *inserare(Nod *radacina, int cheie){
    if(radacina == NULL)
        return creeazaNod(cheie);

    if(cheie < radacina -> cheie)
        radacina -> stanga = inserare(radacina -> stanga, cheie);
    else
        radacina -> dreapta = inserare(radacina -> dreapta, cheie);

    return radacina;
}

int readFromFile(char *fileName, Nod **radacina){
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
        int val;
        if(fscanf(file, "%d", &val) != 1){
            perror(NULL);
            exit(-1);
        }
        *radacina = inserare(*radacina, val);
    }

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }

    return nrNoduri;
}

void prerodine(Nod *radacina, int nivel){
    if(radacina == NULL)
        return;

    printf("%d ", radacina -> cheie);
    prerodine(radacina -> stanga, nivel + 1);
    prerodine(radacina -> dreapta, nivel + 1);
}

void freeMemory(Nod *radacina){
    if(radacina == NULL)
        return;

    freeMemory(radacina -> stanga);
    freeMemory(radacina -> dreapta);
    //printf("Eliberare nod %d\n", radacina -> cheie);
    free(radacina);
}

int cauta(Nod *radacina, int cheie){
    if(radacina == NULL)
        return 0;

    if(radacina -> cheie == cheie)
        return 1;

    if(cheie < radacina -> cheie)
        return cauta(radacina -> stanga, cheie);
    else
        return cauta(radacina -> dreapta, cheie);
}

int inaltime(Nod *radacina){
    if(radacina == NULL)
        return 0;

    int st = inaltime(radacina -> stanga);
    int dr = inaltime(radacina -> dreapta);

    if(st > dr)
        return 1 + st;
    else
        return 1 + dr;
}

int estePerfect(Nod *radacina, int inaltime, int nivel){
    if(radacina == NULL)
        return 1;

    if(radacina -> stanga == NULL && radacina -> dreapta == NULL){
        inaltime = nivel + 1;
        return inaltime;
    }

    if(radacina -> stanga == NULL || radacina -> dreapta == NULL)
        return 0;

    return estePerfect(radacina -> stanga, inaltime, nivel + 1) && estePerfect(radacina -> dreapta, inaltime, nivel + 1);
}

int main(){
    Nod *radacina = NULL;

    nrNoduri = readFromFile("arboreBinar.txt", &radacina);
    printf("In arbore sunt %d noduri!\n", nrNoduri);

    prerodine(radacina, 0);
    printf("\n\n");

    int elementCautat;
    printf("Introduceti un element: ");
    scanf("%d", &elementCautat);

    if(cauta(radacina, elementCautat))
        printf("Am gasit elementul %d!\n", elementCautat);
    else
        printf("Elementul %d nu se afla in arbore!\n", elementCautat);

    int h = inaltime(radacina);
    printf("\nInaltimea arborelui este: %d\n", h);

    if(estePerfect(radacina, h, 0))
        printf("\nArborele este perfect!\n");
    else
        printf("\nArborele nu este perfect!\n");

    freeMemory(radacina);

    return 0;
}