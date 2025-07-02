#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100
#define INF INT_MAX

int matrice[SIZE][SIZE];
int dist[SIZE];
int vizitat[SIZE];
int parinte[SIZE];
int nrNoduri;

void init(){
    for(int i = 0; i < nrNoduri; i++)
        for(int j = 0; j < nrNoduri; j++)
            if(matrice[i][j] == 0 && i != j)
                matrice[i][j] = INF;
}

void citireNod(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror(NULL);
        exit(-1);
    }

    fscanf(file, "%d", &nrNoduri);

    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            int val;
            fscanf(file, "%d", &val);
            if(val == 0 && i != j)
                matrice[i][j] = INF;
            else
                matrice[i][j] = val;
        }
    }

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }

    init();

    printf("Noduri: %d\n", nrNoduri);
}

void printArray(){
    printf("\n");
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            if(matrice[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(int nodStart){
    for(int i = 0; i < nrNoduri; i++){
        vizitat[i] = 0;
        parinte[i] = nodStart;
        dist[i] = matrice[nodStart][i];
    }

    vizitat[nodStart] = 1;
    dist[nodStart] = 0;

    for(int i = 0; i < nrNoduri; i++){
        int pmin = -1;
        for(int j = 0; j < nrNoduri; j++)
            if(vizitat[j] == 0 && (pmin == -1 || dist[j] < dist[pmin]))
                pmin = j;

        if(pmin == -1)
            break;

        vizitat[pmin] = 1;
        for(int j = 0; j < nrNoduri; j++){
            if(vizitat[j] == 0 && dist[pmin] != INF && matrice[pmin][j] != INF && dist[pmin] + matrice[pmin][j] < dist[j]){
                dist[j] = dist[pmin] + matrice[pmin][j];
                parinte[j] = pmin;
            }
        }
    }
}

void drum(int start, int destination){
    int v[SIZE] = {0};
    int index = 0;

    int i = destination;
    while(i != start){
        v[index++] = i;
        i = parinte[i];
    }

    printf("%d ", start);
    for(int i = index - 1; i >= 0; i--)
        printf("%d ", v[i]);

    if(dist[destination] == INF)
        printf("Nu exista drum de la %d la %d!\n", start, destination);
    else
        printf("    Distanta: %d", dist[destination]);
        
    printf("\n");
}

void afiseazaDrumurile(int start){
    for(int i = 0; i < nrNoduri; i++){
        while(i != start){
            printf("%d -> %d: ", start, i);
            drum(start, i);
        }
    }
}

void display(){
    printf("\nIndex:   ");
    for(int i = 0; i < nrNoduri; i++)
        printf("%d ", i);
    printf("\n");

    printf("Vizitat: ");
    for(int i = 0; i < nrNoduri; i++)
        printf("%d ", vizitat[i]);
    printf("\n");

    printf("Dist   : ");
    for(int i = 0; i < nrNoduri; i++)
        printf("%d ", dist[i]);
    printf("\n");

    printf("Parinte: ");
    for(int i = 0; i < nrNoduri; i++)
        printf("%d ", parinte[i]);
    printf("\n");
}

int main(){
    citireNod("dijkstra.txt");
    printArray();
    dijkstra(0);
    display();
    //drum(0, 2);
    afiseazaDrumurile(0);
    return 0;
}