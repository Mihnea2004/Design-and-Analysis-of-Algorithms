#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Nod {
    struct Nod *alfabet[26];
    int frec;
    bool end;
} Nod;

typedef struct {
    char cuvant[256];
    int frecventa;
} Completari;

Completari completari[256];
int size = 0;

Nod* creareNod() {
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    if (nou == NULL) {
        perror("Error creating node!");
        exit(-1);
    }

    for (int i = 0; i < 26; i++)
        nou->alfabet[i] = NULL;

    nou->frec = 0;
    nou->end = false;

    return nou;
}

void addWord(Nod *radacina, char *cuvant) {
    if (radacina == NULL)
        return;

    Nod *current = radacina;
    current->frec++;

    for (int i = 0; i < strlen(cuvant); i++) {
        int index = cuvant[i] - 'A';

        if (current->alfabet[index] == NULL)
            current->alfabet[index] = creareNod();

        current = current->alfabet[index];
        current->frec++;
    }

    current->end = true;
}

void parcurgere(Nod *radacina, char *buffer, int index, int afisare) {
    if (radacina == NULL)
        return;

    if (radacina->end == true) {
        buffer[index] = '\0';
        if (afisare)
            printf("%s\n", buffer);

        if (size < 50) {
            strcpy(completari[size].cuvant, buffer);
            completari[size++].frecventa = radacina->frec;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (radacina->alfabet[i] != NULL) {
            buffer[index] = 'A' + i;
            parcurgere(radacina->alfabet[i], buffer, index + 1, afisare);
        }
    }
}

void prefixComun(Nod *radacina, char *prefix, int afisare) {
    if (radacina == NULL)
        return;

    Nod *current = radacina;
    for (int i = 0; i < strlen(prefix); i++) {
        int index = prefix[i] - 'A';
        if (current->alfabet[index] == NULL) {
            printf("Nu exista!\n");
            return;
        }
        current = current->alfabet[index];
    }

    char buffer[256];
    strcpy(buffer, prefix);
    parcurgere(current, buffer, strlen(prefix), afisare);
}

void citire(Nod **radacina, const char *file_name) {
    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        perror("Error opening file!");
        exit(-1);
    }
    char query[200];
    while (fscanf(f, "%199s", query) == 1) {
        addWord(*radacina, query);
    }
    if (fclose(f) != 0) {
        perror("Error closing file!");
        exit(-1);
    }
}

int compare(const void *e1, const void *e2) {
    const Completari *x = (const Completari *)e1;
    const Completari *y = (const Completari *)e2;

    return y->frecventa - x->frecventa;
}

void autocomplete(Nod *radacina, char *prefix, int nivel) {
    size = 0;
    prefixComun(radacina, prefix, 0);

    qsort(completari, size, sizeof(Completari), compare);

    for (int i = 0; i < size && i < nivel; i++) {
        printf("Cuvant: %s, frecventa: %d\n", completari[i].cuvant, completari[i].frecventa);
    }
}

int main() {
    Nod *radacina = creareNod();
    citire(&radacina, "ex3.txt");

    char buffer[256];

    printf("Parcurgere completa:\n");
    parcurgere(radacina, buffer, 0, 1);

    printf("\nPrefix comun 'SU':\n");
    prefixComun(radacina, "SU", 1);

    printf("\nAutocomplete pentru 'ca':\n");
    autocomplete(radacina, "TIP", 5);

    return 0;
}
