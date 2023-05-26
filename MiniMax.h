#include "heuristica.h"

#ifndef profunditat

#define profunditat 6 //es pot triar 2, 4 o 6 (també funciona amb 3 i 5 però no funciona millor que 2 i 4 respectivament)

void copiarTauler (char pare[N][N],char fill[N][N]);
void ferTirada(char m[N][N], int numFill,int nivell);
int calculaNumFills(char m[N][N]);

Node *crearNode(Node *pare, int numFill, int nivell);
void crearNivell(Node *pare, int nivell);
void crearArbre(Node *arrel, int nivell);

void esborraNode(Node *node);
void esborrarArbre(Node* node);

void mostraNode(Node *node, int nivell);
void recorreArbreRec(Node *arrel,int nivell);

int valorFills(Node *node);
int maxim(Node *node);
int minim(Node *node);
int MiniMax(Node *node, int nivell);

#endif
