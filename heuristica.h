#ifndef N

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define N 8 //dimensions del tauler: NxN
#define R 4 //numero de fitxes en ratlla que has de ficar per guanyar, default=4 però funciona per qualsevol natural
#define victoria 100000 //valor que es dona a un R en ratlla, és molt elevat per diferenciar-se de qualsevol altre cas

typedef struct node{
    char tauler[N][N];
    struct node* *fills;
    int n_fills;
    int valor;
    int log;
}Node;

/*
 La variable log assigna al seu node el valor del numero de fill d'on prové la variable valor. És a dir,
 log indica de quin dels fills s'ha extret el valor que té el node, donat el nostre cas on utilitzem
 l'algortime MiniMax, et diu quin fill era el màxim o el mínim depenent del nivell.
 */

int comprovar_fitxa_C(char m[N][N],int i, int j);
int fitxa_bloqueig_C(char m[N][N],int i, int j);
int comprovar_fitxa_H(char m[N][N],int i, int j);
int fitxa_bloqueig_H(char m[N][N],int i, int j);
int fitxa_suport(char m[N][N],int i, int j);

double kernel_heuristica(int c, int b, int s);

double puntuacio_ddn(char m[N][N], int i, int j);
double puntuacio_ddp(char m[N][N], int i, int j);
double puntuacio_dh(char m[N][N], int i, int j);
double puntuacio_dv(char m[N][N], int i, int j);
int puntuacio(char m[N][N], int i, int j);

int f_heuristica(char m[N][N]);

#endif
