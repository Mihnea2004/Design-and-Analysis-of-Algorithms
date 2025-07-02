#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 20
#define INF INT_MAX

int S[SIZE];
int matrice[SIZE][SIZE];
int nrNoduri, nrMuchii;

int readFromFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        perror(NULL);
        exit(-1);
    }

    if(fscanf(file, "%d", &nrNoduri) != 1){
        perror(NULL);
        exit(-1);
    }

    int u, v, cost;
    while(fscanf(file, "%d %d %d", &u, &v, &cost) == 3){
        matrice[u][v] = cost;
        matrice[v][u] = cost;
        nrMuchii++;
    }

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }

    return nrNoduri;
}

void init(){
    for(int i = 0; i < nrNoduri; i++)
        S[i] = i;
}

void unite(int x, int y){
    int from = S[y];
    int to = S[x];

    for(int i = 0; i < nrNoduri; i++)
        if(S[i] == from)
            S[i] = to;
}

void alegeMuchiaMinima(int *u, int *v){
    int minim = INF;
    *u = -1;
    *v = -1;

    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            if(matrice[i][j] && S[i] != S[j] && matrice[i][j] < minim){
                minim = matrice[i][j];
                *u = i;
                *v = j;
            }
        }
    }
}

void afiseazaMuchiaMinima(){
    int minim = INF, u = -1, v = -1;

    for(int i = 0; i < nrNoduri; i++){
        for(int j = i + 1; j < nrNoduri; j++){
            if(matrice[i][j] && matrice[i][j] < minim){
                minim = matrice[i][j];
                u = i;
                v = j;
            }
        }
    }

    if(u != -1)
        printf("Muchia cu cost minim: %d - %d, Cost: %d\n\n", u, v, minim);
    else
        printf("Nu exista nicio muchie in graf!\n");
}

int kruskal(){
    init();

    int costTotal = 0;
    int pas = 0;
    while(pas < nrNoduri - 1){
        int u, v;
        alegeMuchiaMinima(&u, &v);

        if(u == -1) //nu mai sunt muchii valide, graful nu e conex
            break;

        printf("Muchie: %d - %d, Cost: %d\n", u, v, matrice[u][v]);
        unite(u, v);
        pas++;
        costTotal += matrice[u][v];
    }

    if(pas == nrNoduri - 1)
        printf("Graful este conex!\n");
    else
        printf("Graful NU este conex!\n");

    return costTotal;
}

void bfs(int startNode, int endNode){ //lungimea minima dintre 2 noduri, daca nu ai cost
    int temp = endNode;
    int tata[SIZE] = {0};
    tata[startNode] = -1;

    int coada[SIZE], front = 0, rear = 0;
    int viz[SIZE] = {0};

    coada[rear] = startNode;
    viz[startNode] = 1;

    printf("Parcurgere BFS de la nodul %d: ", startNode);

    while(front <= rear){
        int nodCurent = coada[front];

        for(int i = 0; i < nrNoduri; i++){
            if(matrice[nodCurent][i] != 0 && viz[i] == 0){
                tata[i] = nodCurent;
                coada[++rear] = i;
                viz[i] = 1;
            }
        }
        front++;
    }

    printf("\n");
    for(int i = 0 ; i < nrNoduri; i++)
        printf("%d ", tata[i]);
    printf("\n");

    int count = 0;
    while(tata[endNode] != tata[startNode]){
        count++;
        endNode = tata[endNode];
    }

    printf("\nLungimea minima de la %d la %d este %d\n", startNode, temp, count );

    printf("\n");
}

int componenteConexe(){
    int vizitat[SIZE] = {0};
    int counter = 0;

    for(int i = 0; i < nrNoduri; i++){
        int radacina = S[i];
        if(vizitat[radacina] == 0){
            vizitat[radacina] = 1;
            counter++;
        }
    }

    return counter;
}

int main(){
    nrNoduri = readFromFile("kruskal.txt");
    printf("In graf sunt %d noduri!\n\n", nrNoduri);

    // bfs(0, 3);

    afiseazaMuchiaMinima();

    int cost = kruskal();
    printf("\nCostul total al MST este %d!\n", cost);

    int x = componenteConexe();
    printf("\nComponente conexe: %d\n", x);

    return 0;
}

/*
9
0 1 4
0 7 8
1 7 11
1 2 8
7 8 7
7 6 1
2 8 2
8 6 6
2 3 7
2 5 4
6 5 2
3 5 14
3 4 9
5 4 10
*/