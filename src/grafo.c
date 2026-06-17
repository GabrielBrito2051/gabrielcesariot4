#include <stdio.h>
#include <string.h>
#include "../include/grafo.h"
#include "../include/hashtable.h"

typedef struct Aresta{
    char nome[48], ldir[24], lesq[24], destino[48];
    double cmp, vm;
    struct Aresta* prox;
}aresta;

typedef struct{
    char idString[48];
    double x, y;
    aresta* inicio;
}vertice;

typedef struct{
    int maxVertices;
    int qntdAtual;
    vertice* v;
    Hashtable mapaIds;
}grafo;

int obter_indice(Grafo g, char* idBusca){
    grafo* var = (grafo*)g;
    if(var==NULL || var->mapaIds==NULL) return -1;
    return buscar_hashtable(var->mapaIds, idBusca);
}

aresta* nova_aresta(char* idDestino, double comprimento, double velocidadeMedia, char* ldir, char* lesq){
    aresta* novo = malloc(sizeof(aresta));

    strcpy(novo->destino,idDestino);
    novo->cmp = comprimento;
    novo->vm = velocidadeMedia;
    strcpy(novo-ldir, ldir);
    strcpy(novo->lesq,lesq);

    return novo;
}

Grafo criar_grafo(int numVertices){
    grafo* g = malloc(sizeof(grafo));
    if(g==NULL){
        return NULL;
    }

    g->maxVertices = numVertices;
    g->qntdAtual = 0;
    g->v = malloc(numVertices * sizeof(vertice));
    g->mapaIds = criar_hashtable(numVertices * 2);

    if(g->v==NULL || g->mapaIds==NULL){
        if(g->v) free(g->v);
        if(g->mapaIds) destruir_hashtable(g->mapaIds);
        free(g);
        return NULL;
    }

    for(int i=0;i<numVertices;i++){
        strcpy(g->v[i].idString,"\0");
        g->v[i].inicio = NULL;
        g->v[i].x = 0;
        g->v[i].y = 0;

        return g;
    }
}

void inserir_vertice(Grafo g, int idTexto, double x, double y){
    grafo* var = (grafo*)g;
    if(var==NULL || var->qntdAtual >= var->maxVertices){
        return;
    }

    if(obter_indice(var, idTexto) != -1){
        return;
    }

    int indice = var->qntdAtual;

    strcpy(var->v[indice].idString, idTexto);
    var->v[indice].x = x;
    var->v[indice].y = y;
    var->v[indice].inicio = NULL;

    inserir_hashtable(var->mapaIds, idTexto, indice);

    var->qntdAtual++;
}

void inserir_aresta(Grafo g, char* origem, char* destino, char* ldir, char*lesq, double comprimento, double velocidadeMedia, char* nome){
    if(g==NULL) return;
    grafo* var = (grafo*)g;

    int idOrigem = obter_indice(var, origem);
    int idDestino = obter_indice(var, destino);

    if(idOrigem == -1 || idDestino == -1) return;

    aresta* nova = nova_aresta(idDestino, comprimento, velocidadeMedia, ldir, lesq);
    if(nova==NULL) return;

    nova->prox = var->v[idOrigem].inicio;
    var->v[idOrigem].inicio = nova;
}
/*
Grafo busca_menor_caminho(Grafo g){

}


Grafo busca_menor_tempo(Grafo g){

}
*/

void destruir_grafo(Grafo g){
    if(g==NULL) return;
    grafo* var = (grafo*)g;

    for(int i=0;i<var->qntdAtual;i++){
        aresta* atual = var->v[i].inicio;
        while(atual!=NULL){
            aresta* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }

    destruir_hashtable(var->mapaIds);
    free(var->v);
    free(var);
}