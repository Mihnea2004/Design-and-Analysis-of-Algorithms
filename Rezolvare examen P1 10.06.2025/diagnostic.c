#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct Nod{
    struct Nod *stanga, *dreapta;
    int cheie;
} Nod;

int tata[SIZE];
int nrNoduri;

Nod *creeazaNod(int cheie){
    Nod *nod = malloc(sizeof(Nod));
    if(nod == NULL){
        perror("Error malloc!\n");
        exit(-1);
    }

    nod -> cheie = cheie;
    nod -> stanga = NULL;
    nod -> dreapta = NULL;

    return nod;
}

Nod *insereaza(Nod *radacina, int tata_cheie, int cheie){
    if(radacina == NULL)
        return NULL;

    if(radacina -> cheie == tata_cheie){ //am nodul, nu am copii
        Nod *copil = creeazaNod(cheie);
;       if(radacina -> stanga == NULL)
            radacina -> stanga = copil;
        else if(radacina -> dreapta == NULL)
            radacina -> dreapta = copil;
        else{
            printf("Nodul %d are deja 2 copii!\n", tata_cheie);
            return NULL;
        }
    }
    else{
        insereaza(radacina -> stanga, tata_cheie, cheie);
        insereaza(radacina -> dreapta, tata_cheie, cheie);
    }

    return radacina;
}

void citesteIntrebari(char *fileName, Nod **radacina){
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror("Eroare la deschiderea fisierului");
        exit(EXIT_FAILURE);
    }

    if(fscanf(file, "%d", &nrNoduri) != 1){
        perror(NULL);
        exit(-1);
    }

    for(int i = 1; i <= nrNoduri; i++){
        fscanf(file, "%d", &tata[i]);
    }

    for(int i = 1; i <= nrNoduri; i++)
        if(tata[i] == 0)
            *radacina = creeazaNod(i);
        else
            *radacina = insereaza(*radacina, tata[i], i);

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }

    printf("Noduri: %d\n", nrNoduri);
}

void citesteRaspunsuri(char *fileName, Nod *radacina, Nod **ultimaPozitie){
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror("Eroare la deschiderea fisierului");
        exit(EXIT_FAILURE);
    }

    int raspuns;
    Nod *current = radacina;

    while((fscanf(file, "%d", &raspuns) == 1) && current != NULL && (current -> stanga != NULL || current -> dreapta != NULL)){
        if(raspuns == 1 && current -> stanga != NULL)
            current = current -> stanga;
        else if(current -> dreapta != NULL)
            current = current -> dreapta;
    }

    *ultimaPozitie = current;

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }
}

void preordine(Nod *radacina){
    if(radacina == NULL)
        return;

    printf("%d ", radacina -> cheie);

    preordine(radacina -> stanga);
    preordine(radacina -> dreapta);
}

int intrebariRamase(Nod *ultimaPozitie){
    int counter = 0;
    while(ultimaPozitie != NULL && (ultimaPozitie -> stanga != NULL || ultimaPozitie -> dreapta != NULL)){
        if(ultimaPozitie -> stanga != NULL)
            ultimaPozitie = ultimaPozitie -> stanga;
        else
            ultimaPozitie = ultimaPozitie -> dreapta;
        counter++;
    }

    return counter;
}

int inaltimeMaxima(Nod *radacina){
    if(radacina == NULL)
        return 0;

    int st = inaltimeMaxima(radacina -> stanga);
    int dr = inaltimeMaxima(radacina -> dreapta);

    if(st > dr)
        return st + 1;
    else
        return dr + 1;
}

void freeMemory(Nod *radacina){
    if(radacina == NULL) 
        return;

    freeMemory(radacina->stanga);
    freeMemory(radacina->dreapta);
    free(radacina);
}

int main(){
    Nod *radacina = NULL;
    citesteIntrebari("intrebari.txt", &radacina);

    printf("\nPreordine: ");
    preordine(radacina);

    Nod *ultimaPozitie = NULL;
    citesteRaspunsuri("pacient.txt", radacina, &ultimaPozitie);

    if(ultimaPozitie != NULL)
        printf("\n\nPacientul s-a oprit la nodul %d!\n", ultimaPozitie -> cheie);
    else   
        printf("A fost pus cu succes diagnosticul!\n");

    printf("\nAu mai ramas %d intrebari pana la diagnostic!\n", intrebariRamase(ultimaPozitie));

    printf("\nInaltime maxima: %d\n", inaltimeMaxima(radacina) - 1);

    freeMemory(radacina);

    return 0;
}