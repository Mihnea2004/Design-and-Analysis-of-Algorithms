#include <stdint.h>
#include <stdlib.h>

Nod* creareNod(int valoare);

Nod* inserareNod(Nod* radacina, int valoare);

void preordine(Nod* radacina);

void eliberareMemorie(Nod* radacina);

void adaugaNod(Nod* radacina, int valoare, int parinte);