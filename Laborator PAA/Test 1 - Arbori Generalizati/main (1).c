#include <stdio.h>
#include <stdint.h>
#include <stdint.h>

typedef uint8_t TKey;

typedef struct TNode{
	TKey key;
	struct TNode* parent;
	struct TNode* leftChild;
	struct TNode* rightSibling;
}TNode;

typedef TNode *TNodeRef;

typedef struct {
	TNodeRef *radacina;
}TTree;

TTree InitTree(TTree a) {
	a.radacina = NULL;

	return a;
}

TNodeRef createNode(TKey key, TNodeRef parent) {
	TNodeRef nodNou = malloc(sizeof(TNodeRef));

	nodNou->key = key;
	nodNou->parent = parent;
	nodNou->leftChild = NULL;
	nodNou->rightSibling = NULL;

	return nodNou;
}

TTree InsertNode(TTree a, TNodeRef parent, TKey key) {
	if (a.radacina == NULL) {
		a.radacina = createNode(key, parent);
		return a;
	}

	if(key < a.radacina->key)


	return a;
}

void printArray(TTree a) {
	printf("\nIndex: ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", i);
	}
	printf("\nKey:   ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].key);
	}
	printf("\nParent:");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].parent);
	}
	printf("\n------------------------------------");
}

void printNode(TNode node, char* message) {
	printf("\n%s Key: %d, Parent: %d\n", message, node.key, node.parent);
}

TNodeRef getRoot(TTree a) {
	if (a.size < 1)
		return 0;

	return 1;
}


void preordine(TTree arbore, TNodeRef radacina) {
	printNode(nodeByRef(arbore, radacina), " "); //prima data afisez radacina

	TNodeRef fiuStanga = firstChild(arbore, radacina);
	if (fiuStanga != 0)
		preordine(arbore, fiuStanga);

	TNodeRef fiuDreapta = fiuStanga;
	while ((fiuDreapta = rightSibling(arbore, fiuDreapta)) != 0)
		preordine(arbore, fiuDreapta);
}

void inordine(TTree arbore, TNodeRef radacina) {
	TNodeRef fiuStanga = firstChild(arbore, radacina);
	if (fiuStanga != 0)
		inordine(arbore, fiuStanga);

	printNode(nodeByRef(arbore, radacina), "");

	TNodeRef fiuDreapta = fiuStanga;
	while ((fiuDreapta = rightSibling(arbore, fiuDreapta)) != 0)
		inordine(arbore, fiuDreapta);
}

void postordine(TTree arbore, TNodeRef radacina) {
	TNodeRef fiuStanga = firstChild(arbore, radacina);
	if (fiuStanga != 0)
		postordine(arbore, fiuStanga);

	TNodeRef fiuDreapta = fiuStanga;
	while ((fiuDreapta = rightSibling(arbore, fiuDreapta)) != 0)
		postordine(arbore, fiuDreapta);

	printNode(nodeByRef(arbore, radacina), "");
}

int main(int argc, char* argv[]) {
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		perror(argv[1]);
		exit(-1);
	}

	TTree arbore = { 0, 0 };
	arbore = InitTree(arbore);

	TNodeRef parinte;
	TKey cheie;

	while (fscanf(file, "%hhu %hhu", &cheie, &parinte) == 2) {
		printf("%hhu %hhu", cheie, parinte);
		arbore = InsertNode(arbore, parinte, cheie);
	}

	printArray(arbore);

	printf("\nPreordine\n");
	if (getRoot(arbore) != 0)
		preordine(arbore, 1);

	printf("\nInordine\n");
	if (getRoot(arbore) != 0)
		inordine(arbore, 1);

	printf("\nPostordine\n");
	if (getRoot(arbore) != 0)
		postordine(arbore, 1);

	if (fclose(file) != 0) {
		perror(NULL);
		exit(-1);
	}
	return 0;
}