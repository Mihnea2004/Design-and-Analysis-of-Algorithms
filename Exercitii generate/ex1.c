/*
O agenție spațială a lansat mai mulți sateliți care trebuie să comunice între ei pentru a transmite semnalul de la un punct de colectare 
a datelor spre centrul de comandă.

Rețeaua este reprezentată ca un graf orientat.

Fiecare satelit poate transmite semnalul doar către anumiți alți sateliți aflați în raza lui.

Fiecare conexiune are un cost energetic (număr întreg pozitiv).

La începutul execuției se oferă:

lista conexiunilor: satelit1 satelit2 cost

satelitul de plecare și satelitul destinație

Cerințe:
    Afișează costul minim de transmitere a semnalului de la sursă la destinație.
    Afișează toate nodurile intermediare de pe traseul optim.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE 100
#define INF INT_MAX

int matrice[SIZE][SIZE];
int vizitat[SIZE];
int nrNoduri;
int dist[SIZE];
int parinte[SIZE];

void init(){
    for(int i = 0; i < nrNoduri; i++)
        for(int j = 0; j < nrNoduri; j++)
            if(matrice[i][j] == 0 && i != j)
                matrice[i][j] = INF;
}

void readFromFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror("Eroare la deschiderea fisierului");
        exit(EXIT_FAILURE);
    }

    char a, b;
    int cost;

    while(fscanf(file, " %c %c %d", &a, &b, &cost) == 3){
        int u = a - 'A';
        int v = b - 'A';
        matrice[u][v] = cost;

        if(u + 1 > nrNoduri)
            nrNoduri = u + 1;
        if(v + 1 > nrNoduri)
            nrNoduri = v + 1;
    }

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }

    init();

    printf("\nNoduri: %d\n", nrNoduri);
}

void display(){
    printf("Index:   ");
    for(int i = 0; i < nrNoduri; i++)
        printf("%d ", i);
    printf("\n");

    printf("Vizitat: ");
    for(int i = 0; i < nrNoduri; i++)
        printf("%d ", vizitat[i]);
    printf("\n");

    printf("Dist:    ");
    for(int i = 0; i < nrNoduri; i++)
        printf("%d ", dist[i]);
    printf("\n");

    printf("Parinte: ");
    for(int i = 0; i < nrNoduri; i++)
        printf("%d ", parinte[i]);
    printf("\n\n");
}

void displayMatrix(){
    printf("Matricea de costuri/adiacenta: \n");
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            if(matrice[i][j] == INF)
                printf(" - ");
            else
                printf("%2d ", matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void dijkstra(int nodStart){
    for(int i = 0; i < nrNoduri; i++){
        vizitat[i] = 0;
        dist[i] = matrice[nodStart][i];
        parinte[i] = nodStart;
    }

    vizitat[nodStart] = 1;
    dist[nodStart] = 0;

    for(int i = 0; i < nrNoduri; i++){
        int pmin = -1;
        for(int j = 0; j < nrNoduri; j++){
            if(matrice[i][j] == 0 && (pmin == -1 || dist[j] < dist[pmin]))
                pmin = j;
        }

        if(pmin == -1)
            break;

        vizitat[pmin] = 1;
        for(int j = 0; j < nrNoduri; j++){
            if(matrice[pmin][j] != INF && dist[pmin] != INF && vizitat[j] == 0 && dist[pmin] + matrice[pmin][j] < dist[j]){
                dist[j] = dist[pmin] + matrice[pmin][j];
                parinte[j] = pmin;
            }
        }
    }
}

void drum(int start, int destination){
    int i = destination;
    int index = 0;
    char v[SIZE] = {0};

    while(i != start){
        v[index++] = i;
        i = parinte[i];
    }

    printf("%c ", start + 'A');
    for(int i = index - 1; i >= 0; i--)
        printf("%c ", v[i] + 'A');

    if(dist[destination] == INF)
        printf("Nu exista drum!\n");
    else
        printf("Cost: %d\n", dist[destination]);
}

void afiseazaToateDrumurile(int start){
    for(int i = 0; i < nrNoduri; i++){
        if(i != start){
            printf("%c -> %c: ", start + 'A', i + 'A');
            drum(start, i);
        }
    }
}

int main(){
    readFromFile("comexiuni.txt");
    displayMatrix();

    printf("\nDijkstra: \n");
    dijkstra(0);
    display();

    afiseazaToateDrumurile(0);
}
