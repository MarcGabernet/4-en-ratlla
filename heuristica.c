#include "heuristica.h"

//analitzar l'estat actual del joc i donar valors de 1 o 0 depén de si compleixen els requisits

//si hi ha una fitxa de l'ordenador (C de computer) en (i,j) el valor és 1, si no és 0
int comprovar_fitxa_C(char m[N][N],int i, int j){
    if(m[i][j]=='X'){//X=fitxa ordenador
        return 1;
    }else{
        return 0;
    }
}
//si hi ha una fitxa del jugador (H de humà) en (i,j) el valor és 1, si no és 0
int comprovar_fitxa_H(char m[N][N],int i, int j){
    if(m[i][j]=='O'){ //O=fitxa jugador
        return 1;
    }else{
        return 0;
    }
}
//si hi ha una fitxa del jugador contrari en (i,j) que bloqueja la possibilitat de completar
//un 4 en ralla del jugador corresponent el valor és 0, si no és 1.
int fitxa_bloqueig_C(char m[N][N],int i, int j){
    int v=1-comprovar_fitxa_H(m, i, j);
    return v;
    
    /* Una definició alternativa és aquesta i el mateix funciona per fitxa_bloqueig_H
     
    if(m[i][j]=='H'){
        return 0;
    }else{
        return 1;
    }*/
}
int fitxa_bloqueig_H(char m[N][N],int i, int j){
    int v=1-comprovar_fitxa_C(m, i, j);
    return v;
}

//si hi ha una fitxa a (i,j+1), és a dir just a sota d'on estem avaluant, i la casella està lliure el valor és 1 sinó 0 (fitxa de suport)
int fitxa_suport(char m[N][N],int i, int j){
    if((j==(N-1) || m[i][j+1]!=' ') && m[i][j]==' '){
        return 1;
    }
    return 0;
}
/*
 La següent funció és la que dona valor a les fitxes, el nucli de la funcio heuristica. Tot i que es divideix per c, el resutat final
 de la funció heuristica és enter degut a que s'avalua c vegades la mateixa possibilitat de fer 4 en ralla, on c és el numero de
 fitxes ja colocades en aquesta.
 Una versió també testada d'aquest nucli de l'heuristica és la mateixa funció sense dividir per c, que acaba donant molta més
 importancia a possiblitats de completar el 4 en ralla més complerts degut a que es compta el mateix cas com si fossin c casos diferents.
 */
double kernel_heuristica(int c, int b, int s){
    double v=b*(pow(2,2*(c-1)+s)/c);
    return v;
}

/*
 Les funcions puntuacio_dx retornen un valor que calcula quants "punts" s'ha de donar a una fitxa
 a la cooredenada (i,j) tenint en compte si es pot completar un 4 en ralla utilitzant (i,j) en la
 direcció dx: ddp, ddn, dh, dv. Té en compte com de complert està el 4 en ralla en la posibilitat
 que està avaluant, comptant quantes fitxes hi ha i quants punts de suport en els llocs on encara
 no hi ha fitxa. A més el valor és positiu si la fitxa que estem avaluant és de l'ordenador,
 negatiu si és del jugador i 0 si no hi ha cap fitxa on estem avaluant la puntuació.
 */

double puntuacio_ddn(char m[N][N], int i, int j){ //ddn= direció diagonal negativa
    double v=0;
    int c=0;
    int s=0;
    int b;
    
    if(comprovar_fitxa_C(m, i, j)==1){
        for(int k=0; k<R; k++){
            b=1;
            c=0;
            s=0;
            for(int l=0; l<R; l++){
                if(i-(R-1)+k+l<0 || j-(R-1)+k+l<0 || i-(R-1)+k+l>N-1 || j-(R-1)+k+l>N-1){
                    b=0;
                }else{
                    c=c+comprovar_fitxa_C(m,i-(R-1)+k+l,j-(R-1)+k+l);
                    s=s+fitxa_suport(m,i-(R-1)+k+l,j-(R-1)+k+l);
                    b=b*fitxa_bloqueig_C(m,i-(R-1)+k+l,j-(R-1)+k+l);
                }
            }
            if(c==R){
                v=v+victoria;
            }else{
                v=v+kernel_heuristica(c,b,s);
            }
        }
    }else{
        if(comprovar_fitxa_H(m, i, j)==1){
            for(int k=0; k<R; k++){
                b=1;
                c=0;
                s=0;
                for(int l=0; l<R; l++){
                    if(i-(R-1)+k+l<0 || j-(R-1)+k+l<0 || i-(R-1)+k+l>N-1 || j-(R-1)+k+l>N-1){
                        b=0;
                    }else{
                        c=c+comprovar_fitxa_H(m,i-(R-1)+k+l,j-(R-1)+k+l);
                        s=s+fitxa_suport(m,i-(R-1)+k+l,j-(R-1)+k+l);
                        b=b*fitxa_bloqueig_H(m,i-(R-1)+k+l,j-(R-1)+k+l);
                    }
                }
                if(c==R){
                    v=v-victoria;
                }else{
                    v=v-kernel_heuristica(c,b,s);
                }
            }
        }else{
            v=0;
        }
    }
    return v;
}

double puntuacio_ddp(char m[N][N], int i, int j){ //ddp= direció diagonal positiva
    double v=0;
    int c=0;
    int s=0;
    int b;
    
    if(comprovar_fitxa_C(m, i, j)==1){
        for(int k=0; k<R; k++){
            b=1;
            c=0;
            s=0;
            for(int l=0; l<R; l++){
                if(i-(R-1)+k+l<0 || j+(R-1)-k-l<0 || i-(R-1)+k+l>N-1 || j+(R-1)-k-l>N-1){
                    b=0;
                }else{
                    c=c+comprovar_fitxa_C(m,i-(R-1)+k+l,j+(R-1)-k-l);
                    s=s+fitxa_suport(m,i-(R-1)+k+l,j+(R-1)-k-l);
                    b=b*fitxa_bloqueig_C(m,i-(R-1)+k+l,j+(R-1)-k-l);
                }
            }
            if(c==R){
                v=v+victoria;
            }else{
                v=v+kernel_heuristica(c,b,s);
            }
        }
    }else{
        if(comprovar_fitxa_H(m, i, j)==1){
            for(int k=0; k<R; k++){
                b=1;
                c=0;
                s=0;
                for(int l=0; l<R; l++){
                    if(i-(R-1)+k+l<0 || j+(R-1)-k-l<0 || i-(R-1)+k+l>N-1 || j+(R-1)-k-l>N-1){
                        b=0;
                    }else{
                        c=c+comprovar_fitxa_H(m,i-(R-1)+k+l,j+(R-1)-k-l);
                        s=s+fitxa_suport(m,i-(R-1)+k+l,j+(R-1)-k-l);
                        b=b*fitxa_bloqueig_H(m,i-(R-1)+k+l,j+(R-1)-k-l);
                    }
                }
                if(c==R){
                    v=v-victoria;
                }else{
                    v=v-kernel_heuristica(c,b,s);
                }
            }
        }else{
            v=0;
        }
    }
    return v;
}

double puntuacio_dh(char m[N][N], int i, int j){ //ddp= direció horitzontal
    double v=0;
    int c=0;
    int s=0;
    int b;
    
    if(comprovar_fitxa_C(m, i, j)==1){
        for(int k=0; k<R; k++){
            b=1;
            c=0;
            s=0;
            for(int l=0; l<R; l++){
                if(i-(R-1)+k+l<0 || i-(R-1)+k+l>N-1){
                    b=0;
                }else{
                    c=c+comprovar_fitxa_C(m,i-(R-1)+k+l,j);
                    s=s+fitxa_suport(m,i-(R-1)+k+l,j);
                    b=b*fitxa_bloqueig_C(m,i-(R-1)+k+l,j);
                }
            }
            if(c==R){
                v=v+victoria;
            }else{
                v=v+kernel_heuristica(c,b,s);
            }
        }
    }else{
        if(comprovar_fitxa_H(m, i, j)==1){
            for(int k=0; k<R; k++){
                b=1;
                c=0;
                s=0;
                for(int l=0; l<R; l++){
                    if(i-(R-1)+k+l<0 || i-(R-1)+k+l>N-1){
                        b=0;
                    }else{
                        c=c+comprovar_fitxa_H(m,i-(R-1)+k+l,j);
                        s=s+fitxa_suport(m,i-(R-1)+k+l,j);
                        b=b*fitxa_bloqueig_H(m,i-(R-1)+k+l,j);
                    }
                }
                if(c==R){
                    v=v-victoria;
                }else{
                    v=v-kernel_heuristica(c,b,s);
                }
            }
        }else{
            v=0;
        }
    }
    return v;
}

double puntuacio_dv(char m[N][N], int i, int j){ //dv= direcció vertical
    double v=0;
    int c=0;
    int b=1;
    
    if(comprovar_fitxa_C(m, i, j)==1){
        for(int k=0; k<R; k++){
            b=1;
            c=0;
            for(int l=0; l<R; l++){
                if(j-(R-1)+k+l<0 || j-(R-1)+k+l>N-1){
                    b=0;
                }else{
                    c=c+comprovar_fitxa_C(m,i,j-(R-1)+k+l);
                    b=b*fitxa_bloqueig_C(m,i,j-(R-1)+k+l);
                }
            }
            if(c==R){
                v=v+victoria;
            }else{
                v=v+kernel_heuristica(c,b,1);//sempre hi ha una sola casella de suport si c!=R
            }
        }
    }else{
        if(comprovar_fitxa_H(m, i, j)==1){
            for(int k=0; k<R; k++){
                b=1;
                c=0;
                for(int l=0; l<R; l++){
                    if(j-(R-1)+k+l<0 || j-(R-1)+k+l>N-1){
                        b=0;
                    }else{
                        c=c+comprovar_fitxa_H(m,i,j-(R-1)+k+l);
                        b=b*fitxa_bloqueig_H(m,i,j-(R-1)+k+l);
                    }
                }
                if(c==R){
                    v=v-victoria;
                }else{
                    v=v-kernel_heuristica(c,b,1);//sempre hi ha una sola casella de suport si c!=R
                }
            }
        }else{
            v=0;
        }
    }
    return v;
}
/*
 Suma de les puntuacions en totes les direccions possibles del punt (i,j).
 Ens dona la puntuació total d'una fitxa.
*/
int puntuacio(char m[N][N], int i, int j){
    int valor;
    valor=puntuacio_ddn(m,i,j)+puntuacio_ddp(m,i,j)+puntuacio_dh(m,i,j)+puntuacio_dv(m,i,j);
    return valor;
}

/*
 La funció heuristica finalment suma la puntuacio de totes les caselles del joc: les fitxes C sumen,
 les H resten i les buides tenen valor 0. Només cal sumar la puntuació de cada casella per arribar
 a aquest resultat degut a la manera que hem escrit les funcions puntuacio_dx.
*/

int f_heuristica(char m[N][N]){
    int f=0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            f=f+puntuacio(m,i,j);
        }
    }
    return f;
}
/*
 La idea darrere aquesta funció heuristica ha estat fer una funció simètrica, és a dir, la mateixa situació
 amb les fitxes canviades (C passen a ser H i H passen a C) dona el mateix valor amb el signe canviat.
 Ha estat pensada amb la idea d'analitzar el potencial de cada fitxa i avaluar quant pes té en la situació
 actual del tauler. D'aquesta manera funciona molt bé combinant-la amb l'algoritme MiniMax.
*/
