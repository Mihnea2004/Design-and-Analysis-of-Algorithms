#include <stdint.h>

#define MAXNODES 100

typedef uint8_t TKey;

typedef struct {
	uint8_t parent;
	TKey key;
}TNode;

typedef uint8_t TNodeRef;

typedef struct {
	TNode nodes[MAXNODES];
	uint8_t size; //tree size = number of nodes in the tree	
}TTree;

TTree InitTree(TTree a);

TTree InsertNode(TTree a, TNodeRef  parent, TKey key);

void printArray(TTree a);

void printNode(TNode node, char* message);

TNodeRef parent(TTree a, TNodeRef noderef);

TNodeRef getRoot(TTree a);

TNodeRef findNodeIndex(TTree a, TNode node);

TKey nodeKey(TTree a, TNodeRef noderef);

TNode nodeByRef(TTree a, TNodeRef noderef);

TNodeRef firstChild(TTree a, TNodeRef noderef);

TNodeRef rightSibling(TTree a, TNodeRef noderef);

TTree deleteNode(TTree a, TNodeRef noderef);

void preordine(TTree arbore, TNodeRef radacina);

void inordine(TTree arbore, TNodeRef radacina);

void postordine(TTree arbore, TNodeRef radacina);
