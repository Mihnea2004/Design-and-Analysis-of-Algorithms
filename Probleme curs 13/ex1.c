/*
Un organizator de turneu sportiv trebuie să gestioneze o competiție eliminatorie cu 64 de echipe. 
Fiecare meci elimină o echipă, iar câștigătorii avansează în runda următoare până se stabilește campionul. 
Sistemul trebuie să poată, eficient:
    Urmări ce echipe avansează în fiecare rundă
    Determina traseul oricărei echipe până la poziția finală
    Calcula numărul minim de meciuri necesare
    Găsi toate echipele care au fost eliminate de câștigătorul final

Se cere proiectarea unui algoritm care să reprezinte această structură a turneului și implementarea unor funcții care să răspundă la întrebări 
despre parcursul echipelor și rezultatele meciurilor
*/

#define SIZE 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod{
    char nume[50];
    struct Nod *stanga, *dreapta;
} Nod;

Nod *creeazaFrunza(char *nume){
    Nod *frunza = malloc(sizeof(Nod));
    if(frunza == NULL){
        perror("Eroare creare frunza!\n");
        exit(-1);
    }

    frunza -> stanga = frunza -> dreapta = NULL;
    strcpy(frunza -> nume, nume);

    return frunza;
}

Nod *creeazaNod(Nod *frunza1, Nod *frunza2){
    Nod *nod = malloc(sizeof(Nod));
    if(nod == NULL){
        perror("Eroare creare frunza!\n");
        exit(-1);
    }

    nod -> stanga = frunza1;
    nod -> dreapta = frunza2;

    int optiune;
    do{
        printf("Meci: %s vs %s (1/2): ", frunza1 -> nume, frunza2 -> nume);
        scanf("%d", &optiune);
        if(optiune != 1 && optiune != 2)
            printf("Introduceti 1 sau 2!\n");

        while(getchar() != '\n');
    }  while(optiune != 1 && optiune != 2);

    if(optiune == 1)
        strcpy(nod -> nume, frunza1 -> nume);
    else
        strcpy(nod -> nume, frunza2 -> nume);

    return nod;
}

Nod *creeazaArbore(Nod *echipe[], int st, int dr){
    int mij = (st + dr) / 2;
    if(st == dr)
        return echipe[st];

    Nod *nod1 = creeazaArbore(echipe, st, mij);
    Nod *nod2 = creeazaArbore(echipe, mij + 1, dr);

    return creeazaNod(nod1, nod2);
}

void readFromFile(char *fileName, Nod *echipe[]){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        perror(NULL);
        exit(-1);
    }
    
    char line[256];
    for(int i = 0; i < SIZE; i++){
        if(fgets(line, sizeof(line), file) != NULL){
            line[strcspn(line, "\n")] = '\0';
            echipe[i] = creeazaFrunza(line);
        }
    }
    
    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }
}

void preordine(Nod *radacina, int nivel){
    if(radacina == NULL)
        return;

    printf("%s, ", radacina -> nume);

    preordine(radacina -> stanga, nivel + 1);
    preordine(radacina -> dreapta, nivel + 1);
}

void freeMemory(Nod *radacina){
    if(radacina == NULL)
        return;
        
    freeMemory(radacina -> stanga);
    freeMemory(radacina -> dreapta);
    
    free(radacina);
}

void traseu(Nod *radacina, char *echipaCautata){
    int gasit = 0;
    if(radacina == NULL)
        return;

    if(radacina -> stanga == NULL&& radacina -> dreapta == NULL)
        return;

    if(radacina -> stanga != NULL && strcmp(radacina -> stanga -> nume, echipaCautata) == 0)
        gasit = 1;

    if(radacina -> dreapta != NULL && strcmp(radacina -> dreapta -> nume, echipaCautata) == 0)
        gasit = 1;

    if(gasit)
        printf("%s vs %s -> %s\n", radacina -> stanga -> nume, radacina -> dreapta -> nume, radacina -> nume);
    
    traseu(radacina -> stanga, echipaCautata);
    traseu(radacina -> dreapta, echipaCautata);
}

int numarTotalMeciuri(){
    return SIZE - 1;
}

int main(){
    Nod *echipe[SIZE];
    readFromFile("ex1.txt", echipe);

    Nod *radacina = creeazaArbore(echipe, 0, SIZE - 1);

    printf("\nPreordine: ");
    preordine(radacina, 0);

    printf("\nIn acest turneu s-au jucat %d meciuri!\n", numarTotalMeciuri());

    printf("\nCastigator: ");
    printf("%s\n", radacina -> nume);

    char echipaCautata[50];
    printf("\nIntroduceti o echipa: ");
    fgets(echipaCautata, sizeof(echipaCautata), stdin);
    echipaCautata[strcspn(echipaCautata, "\n")] = '\0';

    printf("\nTraseu echipa %s: \n", echipaCautata);
    traseu(radacina, echipaCautata);

    freeMemory(radacina);

    // printf("\nEchipe: ");
    // for(int i = 0; i < SIZE; i++)
    //     printf("%s ", echipe[i] -> nume);
    return 0;
}