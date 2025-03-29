#include<stdio.h>
#include<stdint.h>
#include"Arbore.h"

TTree InitTree(TTree a) {
	for (int i = 0; i < MAXNODES; i++) {
		a.nodes[i].primFiu = 0;
		a.nodes[i].frateDreapta = 0;
		a.nodes[i].key = 0;
	}
	a.size = 0;
	return a;
}

TTree InsertNode(TTree a, TNodeRef primFiu, TNodeRef frateDreapta, TKey key) {
	a.size++;
	a.nodes[a.size].key = key;
	a.nodes[a.size].primFiu = primFiu;
	a.nodes[a.size].frateDreapta = frateDreapta;
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
	printf("\PrimFiu:");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].primFiu);
	}
	printf("\FrateDreapta:");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].frateDreapta);
	}
	printf("\n------------------------------------");
}

void printNode(TNode node, char* message) {
	printf("\n%s Key: %d, PrimFiu: %d, FrateDreapta: %d\n", message, node.key, node.primFiu, node.frateDreapta);
}

TNodeRef getRoot(TTree a) {
	if (a.size < 1) 
		return 0;

	return 1;
}

TKey nodeKey(TTree a, TNodeRef noderef) {
	if (noderef > a.size) return 0;
	return a.nodes[noderef].key;
}

TNode nodeByRef(TTree a, TNodeRef noderef) {
	return a.nodes[noderef];
}

void preordine(TTree arbore, TNodeRef radacina) {
	printNode(nodeByRef(arbore, radacina), " ");

	TNodeRef fiuStanga = arbore.nodes[radacina].primFiu;
	if (fiuStanga != 0)
		preordine(arbore, fiuStanga);

	TNodeRef fiuDreapta = fiuStanga;
	while((fiuDreapta = arbore.nodes[radacina].frateDreapta) != 0)
		preordine(arbore, fiuDreapta);
}