#include "../include/quadra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char cep[48];
    double x, y, w, h;
}quadra;

typedef struct{
    char sw[8], fill[32], strk[32];
}estilo;

Quadra criar_quadra(char* cep, double x, double y, double w, double h){
    quadra* novo = calloc(1, sizeof(quadra));
    strcpy(novo->cep,cep);
    novo->x = x;
    novo->y = y;
    novo->w = w;
    novo->h = h;

    return novo;
}

char* getCepQuadra(Quadra q){
    return ((quadra*)q)->cep;
}

double getXQuadra(Quadra q){
    return ((quadra*)q)->x;
}

double getYQuadra(Quadra q){
    return ((quadra*)q)->y;
}

double getWQuadra(Quadra q){
    return ((quadra*)q)->w;
}

double getHQuadra(Quadra q){
    return ((quadra*)q)->h;
}

double calculaXEndereco(Quadra q, char face, int num){
    quadra* var = (quadra*) q;
    double x = var->x;
    if(face=='N'){
        x = var->x + num;
    }
    else if(face=='S'){
        x = var->x + num;
    }
    else if(face=='O' || face=='W'){
        x = var->x + var->w;
    }

    return x;
}

double calculaYEndereco(Quadra q, char face, int num){
    quadra* var = (quadra*) q;
    double y = var->y;
    if(face=='N'){
        y = var->y + var->h;
    }
    else if(face=='L' || face=='E'){
        y = var->y + num;
    }
    else if(face=='O' || face=='W'){
        y = var->y + num;
    }

    return y;
}

void liberar_quadra(Quadra q){
    free((quadra*)q);
}

Estilo criar_estilo(char* sw, char* fill, char* strk){
    estilo* novo = malloc(sizeof(estilo));
    strcpy(novo->sw,sw);
    strcpy(novo->fill,fill);
    strcpy(novo->strk,strk);

    return novo;
}

char* getSw(Estilo ts){
    return ((estilo*)ts)->sw;
}

char* getFill(Estilo ts){
    return ((estilo*)ts)->fill;
}

char* getStrk(Estilo ts){
    return ((estilo*)ts)->strk;
}

void setSw(Estilo ts, char* sw){
    strcpy(((estilo*)ts)->sw,sw);
}

void setFill(Estilo ts, char* fill){
    strcpy(((estilo*)ts)->fill,fill);
}

void setStrk(Estilo ts, char* strk){
    strcpy(((estilo*)ts)->strk,strk);
}

void removerEstilo(Estilo ts){
    free((estilo*)ts);
}