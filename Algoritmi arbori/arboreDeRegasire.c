#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

typedef struct Nod{
    struct Nod *alfabet[27];
    int frecventa;
} Nod;

typedef struct{
    char cuvant[SIZE];
    int frecventa;
} Completare;

Completare completari[SIZE];
int size = 0;

Nod *creeazaNod(){
    Nod *nod = malloc(sizeof(Nod));
    if(nod == NULL){
        perror(NULL);
        exit(-1);
    }

    for(int i = 0; i < 27; i++)
        nod -> alfabet[i] = 0;
    nod -> frecventa = 0;

    return nod;
}

void addWord(Nod *radacina, char *cuvant){
    if(radacina == NULL)
        return;

    Nod *current = radacina;
    current -> frecventa++;

    for(int i = 0; i < strlen(cuvant); i++){
        int index = cuvant[i] - 'a';
        if(current -> alfabet[index] == NULL)
            current -> alfabet[index] = creeazaNod();

        current = current -> alfabet[index];
        current -> frecventa++;
    }

    current -> alfabet['{' - 'a'] = current;
}

void readFromFile(char *fileName, Nod **radacina){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        perror("pacient.txt open failed");
        exit(-1);
    }

    char line[256];
    while(fgets(line, sizeof(line), file) != NULL){
        line[strcspn(line, "\n")] = '\0';
        //printf("%s\n", line);
        addWord(*radacina, line);
    }

    if(fclose(file) != 0){
        perror("pacient.txt close failed");
        exit(-1);
    }
}

void parcurgere(Nod *radacina, char *buffer, int index, int afiseaza){
    if(radacina == NULL)
        return;

    if(radacina -> alfabet['{' - 'a'] == radacina){
        buffer[index] = '\0';
        if(afiseaza)
            printf("%s\n", buffer);

        if(size < 50){
            strcpy(completari[size].cuvant, buffer);
            completari[size++].frecventa = radacina -> frecventa;
        }
    }

    for(int i = 0; i < 26; i++){
        if(radacina -> alfabet[i] != NULL){
            buffer[index] = i + 'a';
            parcurgere(radacina -> alfabet[i], buffer, index + 1, afiseaza);
        }
    }
}

void prefixeComune(Nod *radacina, char *prefix, int afiseaza){
    if(radacina == NULL)
        return;

    Nod *current = radacina;

    for(int i = 0; i < strlen(prefix); i++){
        int index = prefix[i] - 'a';
        if(current -> alfabet[index] == NULL){
            printf("Nu exista cuvant cu acest prefix!\n");
            return;
        }
        current = current -> alfabet[index];
    }

    char buffer[SIZE];
    strcpy(buffer, prefix);
    parcurgere(current, buffer, strlen(prefix), afiseaza);
}

int compare(const void *p1, const void *p2){
    const Completare *e1 = (const Completare*) p1;
    const Completare *e2 = (const Completare*) p2;

    return e2 -> frecventa - e1 -> frecventa;
}

void autocomplete(Nod *radacina, char *prefix, int top){
    if(radacina == NULL)
        return;

    size = 0;

    prefixeComune(radacina, prefix, 1);
    qsort(completari, size, sizeof(Completare), compare);

    for(int i = 0; i < size && i < top; i++)
        printf("Cuvant: %s, Frecventa: %d\n", completari[i].cuvant, completari[i].frecventa);
}

void calculeazaLungimeaTotala(Nod *radacina, int nivel, int *sum, int *counter){
    if(radacina == NULL)
        return;

    if(radacina -> alfabet['{' - 'a'] == radacina){ //am ajuns la finalul cuvantului
        *sum += nivel;
        (*counter)++;
    }

    for(int i = 0; i < 26; i++)
        if(radacina -> alfabet[i] != NULL)
            calculeazaLungimeaTotala(radacina -> alfabet[i], nivel + 1, sum, counter);
}

float lungimeMedie(Nod *radacina){
    int sum = 0, counter = 0;
    calculeazaLungimeaTotala(radacina, 0, &sum, &counter);

    if(counter == 0)
        return 0;

    float average = (float) sum / counter;

    return average;
}

int lungimeMaxima(Nod *radacina){
    if(radacina == NULL)
        return 0;

    int maxim = 0;

    for(int i = 0; i < 26; i++){
        if(radacina -> alfabet[i] != NULL){
            int length = lungimeMaxima(radacina -> alfabet[i]);
            if(length > maxim)
                maxim = length;
        }
    }

    return maxim + 1;
}

int numaraCuvintele(Nod *radacina){
    if(radacina == NULL)
        return 0;

    int counter;
    if(radacina -> alfabet['{' - 'a'] == radacina)
        counter = 1;
    else    
        counter = 0;

    for(int i = 0; i < 26; i++)
        counter += numaraCuvintele(radacina -> alfabet[i]);

    return counter;
}

int main(){
    Nod *radacina = creeazaNod();
    readFromFile("arboreDeRegasire.txt", &radacina);

    char buffer[SIZE] = "";
    printf("\nParcurgere: \n");
    parcurgere(radacina, buffer, 0, 1);

    printf("\nPrefixe comune: \n");
    prefixeComune(radacina, "ca", 1);

    autocomplete(radacina, "ti", 4);

    printf("\nCuvinte: %d\n", numaraCuvintele(radacina));
    printf("\nLungimea medie a numelor: %.2f\n", lungimeMedie(radacina));
    printf("\nLungimea celui mai lung cuvant: %d\n", lungimeMaxima(radacina) - 1);
}