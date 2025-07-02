/*O echipă de planificare pentru situații de urgență trebuie să simuleze evacuarea unui complex mare de clădiri interconectate. 
Fiecare clădire are ieșiri spre alte clădiri sau zone de evacuare. Sistemul trebuie să:
    Identifice toate rutele posibile de evacuare dintr-o clădire dată
    Găsească ruta cea mai rapidă către o zonă de evacuare
    Determine dacă există blocaje care izolează complet anumite clădiri
    Evalueze care ieșiri sunt cele mai critice pentru evacuare în siguranță
Se dă o listă de conexiuni între clădiri și timpul necesar pentru traversare. Proiectează o soluție care poate răspunde rapid la interogări 
despre siguranța și eficiența evacuării.
*/

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

void citireNod(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror("Eroare la deschiderea fișierului");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &nrNoduri);

    for(int i = 0; i < nrNoduri; i++) {
        for(int j = 0; j < nrNoduri; j++) {
            int val;
            fscanf(file, "%d", &val);
            if(val == 0 && i != j)
                matrice[i][j] = INF;
            else
                matrice[i][j] = val;
        }
    }

    fclose(file);
    printf("Noduri citite: %d\n", nrNoduri);
}

void printArray() {
    printf("\nMatricea ponderilor:\n");
    for(int i = 0; i < nrNoduri; i++) {
        for(int j = 0; j < nrNoduri; j++) {
            if(matrice[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(int nodStart) {
    for(int i = 0; i < nrNoduri; i++) {
        vizitat[i] = 0;
        dist[i] = matrice[nodStart][i];
        if(matrice[nodStart][i] != INF && i != nodStart)
            parinte[i] = nodStart;
        else
            parinte[i] = -1;
    }

    vizitat[nodStart] = 1;
    dist[nodStart] = 0;
    parinte[nodStart] = -1;

    for(int i = 1; i < nrNoduri; i++) {
        int pmin = -1;
        for(int j = 0; j < nrNoduri; j++)
            if(!vizitat[j] && (pmin == -1 || dist[j] < dist[pmin]))
                pmin = j;

        if(pmin == -1)
            break;

        vizitat[pmin] = 1;
        for(int j = 0; j < nrNoduri; j++) {
            if(!vizitat[j] && matrice[pmin][j] != INF && dist[pmin] != INF &&
               dist[pmin] + matrice[pmin][j] < dist[j]) {
                dist[j] = dist[pmin] + matrice[pmin][j];
                parinte[j] = pmin;
            }
        }
    }
}

void drum(int start, int destination) {
    if(dist[destination] == INF) {
        printf("Nu exista drum de la %d la %d!\n", start, destination);
        return;
    }

    int v[SIZE], index = 0, i = destination;
    while(i != -1) {
        v[index++] = i;
        i = parinte[i];
    }

    for(int j = index - 1; j > 0; j--)
        printf("%d -> ", v[j]);
    printf("%d   Distanta: %d\n", v[0], dist[destination]);
}

void afiseazaDrumurile(int start) {
    printf("\nDrumuri minime de la nodul %d:\n", start);
    for(int i = 0; i < nrNoduri; i++) {
        if(i != start) {
            printf("%d -> %d: ", start, i);
            drum(start, i);
        }
    }
}

void display() {
    printf("\nIndex   : ");
    for(int i = 0; i < nrNoduri; i++) printf("%d ", i);
    printf("\nVizitat : ");
    for(int i = 0; i < nrNoduri; i++) printf("%d ", vizitat[i]);
    printf("\nDistanta: ");
    for(int i = 0; i < nrNoduri; i++) printf("%d ", dist[i]);
    printf("\nParinte : ");
    for(int i = 0; i < nrNoduri; i++) printf("%d ", parinte[i]);
    printf("\n");
}

void blocaj(){
    int esteBlocat = 0;
    for(int i = 0; i < nrNoduri; i++){
        esteBlocat = 0;
        for(int j = 0; j < nrNoduri; j++){
            if(i != j && matrice[i][j] == INF){
                esteBlocat = 1;
                break;
            }
        }
    }

    if(esteBlocat){
        printf("Exista blocaje care izoleaza complet anumite cladiri!\n");
    }
}

int main() {
    citireNod("ex3.txt");
    printArray();
    int start = 0;
    dijkstra(start);
    display();
    afiseazaDrumurile(start);
    blocaj();
    return 0;
}