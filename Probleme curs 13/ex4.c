/*
O platformă de social media dorește să analizeze conexiunile dintre utilizatori pentru a înțelege formarea comunităților. 
Având date despre prieteniile dintre utilizatori, platforma trebuie să:
    Identifice grupurile izolate de prieteni care nu au conexiuni cu alte grupuri
    Determine dimensiunea celui mai mare cerc de prieteni
    Găsească utilizatori care ar putea acționa ca punți între diferite comunități
    Calculeze câte grupuri sociale separate există în rețea
*/

#include <stdio.h>
#include <stdlib.h>

int matrice[50][50];
int nrNoduri;
int vizitat[50];
int A[50][50];

void readFromFile(char *fileName){
    FILE* file = fopen(fileName, "r");
	if(file == NULL){
		perror("Error opening file!");
		exit(-1);
	}

    if(fscanf(file, "%d", &nrNoduri) != 1){
        perror(NULL);
        exit(-1);
    }

    int x, y;
    while(fscanf(file, "%d %d", &x, &y) == 2){
        matrice[x][y] = 1;
        matrice[y][x] = 1;
        A[x][y] = A[y][x] = 1;
    }

    if(fclose(file) != 0){
		perror("Error closing file!");
		exit(-1);
	}
}

void printMatrix(){
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++)
            printf("%d ", matrice[i][j]);
        printf("\n");
    }
    printf("\n");
}

int dfs(int nod){
    vizitat[nod] = 1;
    //printf("%d ", nod);
    int dim = 1;

    for(int i = 0; i < nrNoduri; i++)
        if(matrice[nod][i] != 0 && vizitat[i] == 0)
            dim += dfs(i);
    

    return dim;
}

void init(){
    for(int i = 0; i < nrNoduri; i++)
        vizitat[i] = 0;
}

int componenteConexe(){
    int counter = 0;
    init();

    int maxim = 0;
    for(int i = 0; i < nrNoduri; i++){
        if(vizitat[i] == 0){
            counter++;
            int dim = dfs(i);
            // printf("Componenta %d are %d membrii\n", counter, dim);
            if(dim > maxim)
                maxim = dim;
        }
    }

    printf("\nCel mai mare grup de prieteni are %d membri\n", maxim);

    return counter;
}

void stergeMuchii(){
    int componenteVechi = componenteConexe();
    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            if(matrice[i][j]){
                matrice[i][j] = 0;
                matrice[j][i] = 0;
            }
        }
        int componenteNoi = componenteConexe() - 1;
        printf("Pentru nodul %d: ", i);
        if(componenteNoi > componenteVechi)
            printf("sunt %d componente noi\n", componenteNoi);
        else
            printf("nu sunt componente noi!\n");

        for(int j = 0; j < nrNoduri; j++){
            if(A[i][j]){
                matrice[i][j] = 1;
                matrice[j][i] = 1;
            }
        }
    }
}

int main(){
    readFromFile("ex4.txt");
    printMatrix();

    printf("\nComponente conexe: %d\n", componenteConexe());

    stergeMuchii();

    return 0;
}