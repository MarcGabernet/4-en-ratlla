#include "MiniMax.h"
#include "4_en_ralla.h"

void copiarTauler (char pare[N][N],char fill[N][N]){
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            fill[i][j]=pare[i][j];
        }
    }
}

void ferTirada(char m[N][N], int numFill,int nivell){
    for(int i=0;i<=numFill;i++){
        if(m[i][0]!=' '){
            numFill++;
        }//suma a numFills per tenir en compte les caselles plenes
    }
    if(parell(nivell)==true){
        m[numFill][tria_suport(m,numFill)]='O';
    }else{
        m[numFill][tria_suport(m,numFill)]='X';
    }
}

int calculaNumFills(char m[N][N]){
    int n=0;
    for(int i=0;i<N; i++){
        if(m[i][0]==' '){
            n++;
        }
    }
    return n;
}

Node *crearNode(Node *pare, int numFill, int nivell){
    Node *p=malloc(sizeof(Node));
    copiarTauler(pare->tauler,p->tauler);
    p->valor=f_heuristica(p->tauler);
    if(abs(p->valor)<(R-1)*victoria+1){ //només es fa tirada si no s'ha fet un 4 en ralla
        ferTirada(p->tauler,numFill,nivell);
        p->valor=f_heuristica(p->tauler);
    }else{
        if(pare->valor>0 && nivell<=profunditat){
            p->valor=pare->valor+(profunditat-nivell)*100;
        }if(pare->valor<0 && nivell<=profunditat){
            p->valor=pare->valor-(profunditat-nivell)*100;
        }
        /*
         En aquesta part del codi incrementem el valor d'un node depenent de en quin nivell arriba a guanyar el contrincant.
         Com més ràpid arriba a una victòria més extrem serà el valor. Durant proves del joc he observat que si no es fica aquest
         else{} a vegades el codi pot triar un fill que no li garanteix una victòria tant immediata, donat que potser observa una
         victòria en un nivell molt més profund i el valor acaba punjant fins al node arrel, i a la vegada, al estar a punt d'executar
         aquell moviment torna a passar el mateix i no s'acaba guanyant mai de part de l'ordenador.
         D'aquesta manera dona més pes a les victòries i derrotes més immediates per poder diferenciar-les de les altres i escollir-les.
         
         Tots els valors de nodes amb nivell<profunditat s'acaben substituint fent servir l'algoritme MiniMax a partir dels valors
         dels nodes de nivell=profunditat. Es calculen igualment primer tots els valors per poder transportar les victories i
         derrotes que s'asoleixen a nivells<profunditat fins a l'últim nivell per a que depres que tornin a pujar.
         */
    }
    if(nivell<profunditat){
        if(abs(p->valor)<(R-1)*victoria+1){
            p->n_fills=calculaNumFills(p->tauler);
        }else{
            p->n_fills=1;
            //només cal fer un fill de partides ja decidides
        }
        p->fills=malloc(p->n_fills*sizeof(Node*));
    }else{
        p->n_fills=0;
        p->fills=NULL;
    }
    return p;
}

void crearNivell(Node *pare, int nivell){
    for(int i=0; i<pare->n_fills;i++){
        pare->fills[i]=crearNode(pare,i,nivell);
    }
}

void crearArbre(Node *arrel, int nivell){//inicialitzar amb nivell=1
    crearNivell(arrel,nivell);
    for(int i=0; i<arrel->n_fills;i++){
        crearArbre(arrel->fills[i],nivell+1);
    }
}

void esborraNode(Node *node){
    free(node);
}

void esborrarArbre(Node* node){
    for(int i=0; i<node->n_fills; i++){
        esborrarArbre(node->fills[i]);
    }
    esborraNode(node);
}

int valorFills(Node *node){
    return node->valor;
}

int maxim(Node *node){
    int max=0;
    if(node->n_fills>0){ //assegura que el nodi tingui almenys un fill
        max=valorFills(node->fills[0]);//donem inicialment un valor que canviarà si en troba un de més gran
        node->log=0;
    }
    for(int i=0;i<node->n_fills;i++){
        if(max<valorFills(node->fills[i])){
            max=valorFills(node->fills[i]);
            node->log=i; //queda registrat dins el node pare quin és el fill amb el valor més gran
        }
    }
    return max;
}

int minim(Node *node){
    int min=0;
    if(node->n_fills>0){
        min=valorFills(node->fills[0]); //donem inicialment un valor que canviarà si en troba un de més petit
        node->log=0;
    }
    for(int i=0;i<node->n_fills;i++){
        if(min>valorFills(node->fills[i])){
            min=valorFills(node->fills[i]);
            node->log=i; //queda registrat dins el node pare quin és el fill amb el valor més petit
        }
    }
    return min;
}

int MiniMax(Node *node, int nivell){ //inicialitzar amb nivell=1
    int col=0;
    if(nivell<=profunditat){
        for(int i=0;i<node->n_fills;i++){
            MiniMax(node->fills[i], nivell+1);
        }
        if(parell(nivell)==false){
            node->valor=maxim(node);
        }else{
            node->valor=minim(node);
        }
    }if(nivell==1){
        
         //al arribar al nivell 1 volem saber el valor log del node perquè serà on tirarem i de la mateixa
         //manera que en la funció ferTirada fem un for() i un if() per tenir en compte les columnes plenes
         
        col=node->log;
        for(int i=0;i<=col;i++){
            if(node->tauler[i][0]!=' '){
                col++;
            }
        }
    }
    return col;
}

void mostraNode(Node *node, int nivell){
    for(int i=0;i<nivell;i++){
        printf("\t");
    }
    printf("%d\n",node->valor);
}

void recorreArbreRec(Node *arrel,int nivell){
    for(int i=0;i<arrel->n_fills;i++){
            recorreArbreRec(arrel->fills[i],nivell+1);
    }
    mostraNode(arrel,nivell);
}
