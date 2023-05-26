#include "MiniMax.h"
#include "4_en_ralla.h"

int tria_suport(char m[N][N], int col){//determina fins on caurà la fitxa depenent de la columna on la tirem
    for(int i=0; i<N;i++){
        if(fitxa_suport(m,col,i)==1){
            return i;
        }
    }
    return -1;
}

int tauler_ple(char m[N][N]){
    int n=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(m[i][j]==' ')
                n=n+1;
        }
    }
    return n;
}

void buidar_tauler(char m[N][N]){//inicialitza el tauler donant el caràcter ' ' a totes les caselles
    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
            m[i][j]=' ';
        }
    }
}

void printar_tauler(char m[N][N]){
    printf("\n");
    for(int j=0; j<N; j++){
        printf("\t");
        for(int h=0; h<N; h++){
            printf("----");
        }
        printf("-");
        printf("\n");
        printf("\t");
        for(int i=0; i<N; i++){
            printf("| %c ",m[i][j]);
        }
        printf("|");
        printf("\n");
    }
    printf("\t");
    for(int h=0; h<N; h++){
        printf("----");
    }
    printf("-");
}

void printar_torn(int torn){
    if(parell(torn)==true){
        printf("\t\tTorn de l'ordenador (X)");
    }else{
        printf("\t\tTorn del jugador (O)");
    }
}

void indexar_columna(void){
    for(int h=0; h<N; h++){
        printf("\t  %d",h+1);
    }
}

bool parell(int torn){ //una manera més entenedora de preguntar si un valor és parell
    if(torn/2==torn/2.0){
        return true;
    }
    return false;
}

int main(){
    Node *copia=malloc(sizeof(Node));
    buidar_tauler(copia->tauler);
    
    printf("\n\t%d EN RATLLA\n\n",R);
    
    int torn=0;
    int decisio;
    int finish=0;
    char ordre;
    
    printf("\tQui comença, el jugador o la màquina?\t(J/M)\t");
    scanf("%c",&ordre);
    printf("\n\n");
    if(ordre=='J' || ordre=='j'){
        torn++;
    }
    
     //Es fa un while per a que es continui jugant mentre ningú hagi fet un 4 en ratlla. És fica de (R-1)*victoria+1
     //com a valor que ha de superar el valor absolut de la funció heuristica per acabar perquè quan es fa un R en ratlla
     //la funció retorna un valor al voltant de R*victòria (donat que R*victòria és moltes magnituds més gran que qualsevol
     //valor que pugui tenir f_heuristica sense fer un R en ratlla) i per tant és un valor que pot distingir entre els dos
     //casos de joc. El +1 d'aquest valor serveix per a que funcioni el cas trivial R=1.
    
    while(finish<(R-1)*victoria){
        Node *p=malloc(sizeof(Node));
        copiarTauler(copia->tauler,p->tauler);
        p->n_fills=calculaNumFills(p->tauler);
        p->fills=malloc(p->n_fills*sizeof(Node*));
        
        indexar_columna();
        printar_torn(torn);
        printar_tauler(p->tauler);
        
        if(tauler_ple(p->tauler)==0){
            printf("\n\n\tEMPAT!!!\n\n");
            return N*N;
        }
        
        if(parell(torn)==true){
            printf("\t pensant...");
            crearArbre(p,1);
            decisio=MiniMax(p,1)+1;
            printf("\t%d",decisio);
        }else{
            printf("\tOn vols tirar?\t");
            scanf("%d", &decisio);
        }
        printf("\n\n\n");
        if(tria_suport(p->tauler, decisio-1)==-1 || decisio>N || decisio<1){
            printf("\n\tAQUESTA COLUMNA ESTÀ PLENA 0 NO EXISTEIX!\n\n");
        }else{
            if(parell(torn)==true){
                p->tauler[decisio-1][tria_suport(p->tauler, decisio-1)]='X';
            }else{
                p->tauler[decisio-1][tria_suport(p->tauler, decisio-1)]='O';
            }
            copiarTauler(p->tauler,copia->tauler);//guarda l'estat actual del joc a un node que no és destruirà
            finish=abs(f_heuristica(p->tauler));
            if(parell(torn)==true){
                esborrarArbre(p);
            }
            torn++;
        }
    }
    indexar_columna();
    printar_tauler(copia->tauler);
    
    if(ordre=='J' || ordre=='j'){ //torna el valor torn al seu valor real
        torn--;
    }
    
    if(f_heuristica(copia->tauler)<0){
        printf("\n\n\tVICTÒRIA DE O EN %d TORNS!!!\n\n\n",torn);
    }else{
        printf("\n\n\tVICTÒRIA DE X EN %d TORNS!!!\n\n\n",torn);
    }
    
    return 64;
}
