#include <stdio.h>
#include<string.h>
#include<stdlib.h>

#define N 3
#define NN 5
#define MAX 100

typedef char TipCheie;

int gasit;

struct Nod{
	TipCheie cheie[MAX];
	struct Pagina* p;
	int contor;
};

typedef struct Nod Nod;

struct Pagina{
	int m;
	struct Pagina* p0;
	Nod e[NN + 1];
};

typedef struct Pagina Pagina;
Nod v;

Pagina* insereaza(Pagina* pag, TipCheie* x, Nod* nod){
	int i, s, d, mij;
	Pagina* q, * r;

	if (!nod){
		strcpy(v.cheie, x);
		v.contor = 1;
		v.p = NULL;
	}
	else
		v = *nod;

	if (pag == NULL) //daca nu exista radacina
    {
		pag = (Pagina*)calloc(sizeof(Pagina), 1);
		pag->e[++pag->m] = v;

		return pag;
	}

	//se cauta binar pozitia cheii x in pagina curenta
	s = 1;
	d = pag->m;
	while (s <= d)
	{
		mij = (s + d) / 2;
		if (strcmp(pag->e[mij].cheie, x) == 0) //gasit
		{
			pag->e[mij].contor++;
			return pag;
		}
		if (strcmp(x, pag->e[mij].cheie) < 0)
			d = mij - 1;
		else
			s = mij + 1;
	}

	//daca este pagina terminala sau daca se propaga insertia
	if (pag->p0 == NULL || nod)
	{
		if (pag->m < NN) //se poate adauga un nod in pagina curenta
		{
			++pag->m;
			for (i = pag->m; i > d + 1; i--)
				pag->e[i] = pag->e[i - 1];
			pag->e[i] = v;
		}
		//pagina curenta pag este plina => supradepasire => pagina trebuie scindata
		else
		{
			Pagina* a = pag;
			Pagina* b = (Pagina*)calloc(sizeof(Pagina), 1);
			pag = (Pagina*)calloc(sizeof(Pagina), 1);

			//scindarea paginii curente
			for (i = 1; i <= N; i++)
				b->e[i] = a->e[i + N];
			a->m = b->m = N;

			//cheia noudului v e cheia de scindare
			if (strcmp(v.cheie, a->e[N].cheie) > 0 && strcmp(v.cheie, b->e[1].cheie) < 0)
				pag->e[++pag->m] = v;
			else
			{
				//ultima cheie a nodului a este folosita la scindare
				if (strcmp(v.cheie, a->e[N].cheie) < 0)
				{
					pag->e[++pag->m] = a->e[N];
					for (i = a->m; i > 1 && strcmp(a->e[i - 1].cheie, v.cheie) > 0; i--)
						a->e[i] = a->e[i - 1];
					a->e[i] = v;
				}
				//prima cheie a nodului a este folosita la scindare
				else
				{
					pag->e[++pag->m] = b->e[1];
					for (i = 1; i < b->m && strcmp(b->e[i + 1].cheie, v.cheie) < 0; i++)
						b->e[i] = b->e[i + 1];
					b->e[i] = v;
				}
			}

			//se refac legaturile intre pagini
			b->p0 = pag->e[1].p; //prima legatura a paginii b devine legatura nodului parinte
			pag->p0 = a;         //prima legatura a nodului parinte devine fostul vecin stanga
			pag->e[1].p = b;     //a doua legatura a nodului parinte devine fostul vecin dreapta
		}
	}
	else
	{
		if (d == 0) //s-a ajuns la cel mai din stanga element => prima legatura
			q = pag->p0;
		else
			q = pag->e[d].p;
		r = insereaza(q, x, NULL);
		if (r != q) //daca pagina in care s-a inserat s-a scindat <=> arborele crescut cu un nivel
		{
			/*se incearca inserarea nodului din pagina scindata in pagina curenta
			in caz de succes, arborele nu va creste in inaltime*/
			pag = insereaza(pag, r->e[1].cheie, &r->e[1]);
			free(r); //se sterge pagina scindata, intrucat nodul a fost inserat intr-o alta pagina
		}
	}

	return pag;
}

void citireNod(Pagina **pag, char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        perror(NULL);
        exit(-1);
    }

    char buffer[1000];
    fgets(buffer, 1000, file);
	buffer[strcspn(buffer, "\n")] = '\0';

	//printf("%s", buffer);
    char *p = strtok(buffer, "|[],");
    while(p != NULL){
        strcpy(p, p + 1); // elimină prima ghilimea
        p[strlen(p) - 1] = 0; // elimină ultima ghilimea
        if((p[0] >= 'A' && p[0] <= 'Z') || (p[0] >= 'a' && p[0] <= 'z')){
			//printf("%s\n", p);
            *pag = insereaza(*pag, p, NULL);
        }
        p = strtok(NULL, "|[],");
    }

    if(fclose(file) != 0){
        perror(NULL);
        exit(-1);
    }
}

void afiseaza(Pagina *pag, int nivel){
    if(pag == NULL)
        return;

    printf("Nivelul %d: ", nivel);
    for(int i = 1; i <= pag->m; i++){
        printf("%s ", pag->e[i].cheie);
    }
    printf("\n");

    afiseaza(pag->p0, nivel + 1);
    for(int i = 1; i <= pag->m; i++)
        afiseaza(pag->e[i].p, nivel + 1);
}

void cautare(Pagina *pag, char *category){
    if(pag == NULL)
        return;

    int st = 1, dr = pag->m, mij;

    while(st <= dr){
        mij = (st + dr) / 2;
        int cmp = strcmp(pag->e[mij].cheie, category);

        if(cmp == 0){
            printf("Gasit: %s (de %d ori)\n", pag->e[mij].cheie, pag->e[mij].contor);
			gasit = 1;
            return;
        }

        if(cmp > 0)
            dr = mij - 1;
        else
            st = mij + 1;
    }

    if(dr == 0)
        cautare(pag->p0, category);
    else
        cautare(pag->e[dr].p, category);
}

int main(){
    Pagina *pag = NULL;
    citireNod(&pag, "arboriB.txt");

    afiseaza(pag, 0);

	cautare(pag, "Chemistry");
	if(gasit == 0){
		printf("Elementul cautat nu a putut fi gasit!\n");
	}
}